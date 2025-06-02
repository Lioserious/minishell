/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 11:12:54 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/02 14:14:39 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	is_valid(char *str)
{
	int	i;

	i = 0;
	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	while (str[i])
	{
		if(!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}
static char	*extract_name(char *arg)
{
	char	*equal;
	char	*append;

	equal = ft_strchr(arg, '=');
	append = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (append)
		return (gc_substr(arg, 0, append - arg));
	else if (equal)
		return (gc_substr(arg, 0, equal - arg));
	else
		return (gc_strdup(arg));
}

static void	export_set_var(t_env_list *env_list, char *name, char *arg)
{
	char	*value;
	char	*equal;
	char	*append;

	equal = ft_strchr(arg, '=');
	append = ft_strnstr(arg, "+=", ft_strlen(arg));
	if (append)
	{
		value = gc_strdup(append + 2);
		append_env_var(env_list, name, value, 1);
	}
	else if ((equal = ft_strchr(arg, '=')))
	{
		value = gc_strdup(equal + 1);
		update_env_var(env_list, name, value, 1);
	}
	else
		update_env_var(env_list, name, NULL, 1);
}
static void	process_export(t_env_list *env_list, char *arg)
{
	char *name;

	name = extract_name(arg);
	if (!is_valid(name))
	{
		ft_putstr_fd("minishell: export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putendl_fd("': not a valid identifier", 2);
		return;
	}
	export_set_var(env_list, name, arg);
}

int	ft_export(t_env_list *env_list, t_cmd_node *node)
{
	int		i;

	i = 1;
	if (!node->cmd[1])
		return (print_export_list(env_list));
	while (node->cmd[i])
	{
		process_export(env_list, node->cmd[i]);
		i++;
	}
	return (0);
}
