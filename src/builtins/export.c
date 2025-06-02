/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:12:54 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/02 09:23:55 by mimalek          ###   ########.fr       */
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
			if (current->value)
			{
				ft_putchar_fd('=', 1);
				ft_putchar_fd('"', 1);
				ft_putstr_fd(current->value, 1);
				ft_putchar_fd('"', 1);
			}
			ft_putchar_fd('\n', 1);
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

static void	append_env_var(t_env_list *env_list, char *name, char *value, int is_export)
{
	t_env_node	*current;
	char		*new_value;

	current = env_list->head;
	while (current)
	{
		if (ft_strcmp(current->name, name) == 0)
		{
			if (current->value)
				new_value = gc_strjoin(current->value, value);
			else
				new_value = gc_strdup(value);
			current->value = new_value;
			current->is_export = is_export;
			return ;
		}
		current = current->next;
	}
	new_value = gc_strdup(value);
	ft_add_env_var(env_list, name, new_value, is_export);
}

int	ft_export(t_env_list *env_list, t_cmd_node *node)
{
	int		i;
	char	*equal;
	char	*name;
	char	*value;
	char	*append;

	if (!node->cmd[1])
		return (print_export_list(env_list));
	i = 1;
	while (node->cmd[i])
	{
		append = ft_strnstr(node->cmd[i], "+=", ft_strlen(node->cmd[i]));
		equal = ft_strchr(node->cmd[i], '=');
		if (append)
		{
			name = gc_substr(node->cmd[i], 0, append - node->cmd[i]);
			value = gc_strdup(append + 2);
			append_env_var(env_list, name, value, 1);
		}
		else if ((equal = ft_strchr(node->cmd[i], '=')))
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
