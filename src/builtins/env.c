/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:53:12 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/07 16:52:01 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_env_list *env_list)
{
	t_env_node	*current;

	if (!env_list)
		return (1);
	current = env_list->head;
	while (current)
	{
		ft_putstr_fd(current->name, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(current->value, 1);
		current = current->next;
	}
	return (0);
}

t_env_list	*init_env_list(void)
{
	t_env_list	*env_list;

	env_list = (t_env_list *)gc_malloc(sizeof(t_env_list));
	env_list->head = NULL;
	env_list->count = 0;
	return (env_list);
}

void	init_env(t_env_list *env_list)
{
	extern char	**environ;
	char		**env;
	char		*equal;
	char		*name;
	char		*value;

	env = environ;
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
