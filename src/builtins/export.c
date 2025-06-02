/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:12:54 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/02 08:39:19 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_env_var(t_env_list *env_list, char *name, char *value, int is_export);

int	print_export_list(t_env_list	*env_list)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
	{
		if (current->is_export)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current->name, 1);
			if (ft_strlen(current->value)
				&& ft_strncmp(current->value, " ", 2) != 0)
				ft_putchar_fd('=', 1);
			ft_putendl_fd(current->value, 1);
		}
		current = current->next;
	}
	return (0);
}

static void	update_env_var(t_env_list *env_list, char *name, char *value, int is_export)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			current->value = gc_strdup(value);
			current->is_export = is_export;
			return ;
		}
		current = current->next;
	}
	ft_add_env_var(env_list, name, value, is_export);
}

int	ft_export(t_env_list *env_list, t_cmd_node *node)
{
	int		i;
	char	*equal;
	char	*name;
	char	*value;

	if (!node->cmd[1])
		return (print_export_list(env_list));
	i = 1;
	while (node->cmd[i])
	{
		equal = ft_strchr(node->cmd[i], '=');
		if (equal)
		{
			name = gc_substr(node->cmd[i], 0, equal - node->cmd[i]);
			value = gc_strdup(equal + 1);
			update_env_var(env_list, name, value, 1);
		}
		else
		{
			update_env_var(env_list, node->cmd[i], "", 1);
		}
		i++;
	}
	return (0);
}
