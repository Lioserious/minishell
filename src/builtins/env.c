/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:53:12 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/06 14:15:43 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_env_list *env_list)
{
	t_env_node	*current;

	if (!env_list)
		env_list->last_exitcode = 1;
	current = env_list->head;
	while (current)
	{
		if (current->value)
		{
			ft_putstr_fd(current->name, 1);
			ft_putchar_fd('=', 1);
			ft_putendl_fd(current->value, 1);
		}
		current = current->next;
	}
	env_list->last_exitcode = 0;
}

t_env_list	*init_env_list(void)
{
	t_env_list	*env_list;

	env_list = (t_env_list *)gc_malloc(sizeof(t_env_list));
	env_list->head = NULL;
	env_list->count = 0;
	env_list->last_exitcode = 0;
	return (env_list);
}

void	init_env(t_env_list *env_list, char **env)
{
	char		*equal;
	char		*name;
	char		*value;

	while (*env)
	{
		equal = ft_strchr(*env, '=');
		if (equal)
		{
			name = gc_substr(*env, 0, equal - *env);
			value = gc_strdup(equal + 1);
			ft_add_env_var(env_list, name, value, 1);
		}
		env++;
	}
}

void	update_shlvl(t_env_list	*env_list)
{
	char	*shlvl_str;
	char	*new_shlvl;
	int		shlvl;

	shlvl_str = get_env_value(env_list, "SHLVL");
	if (shlvl_str)
		shlvl = ft_atoi(shlvl_str) + 1;
	else
		shlvl = 1;
	new_shlvl = gc_itoa(shlvl);
	set_env_var(env_list, "SHLVL", new_shlvl);
}

void	set_env_var(t_env_list *env_list, char *name, char *value)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name + 1)) == 0)
		{
			current->value = gc_strdup(value);
			return ;
		}
		current = current->next;
	}
	return ;
}
