/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:18:21 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/06 14:03:14 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(t_env_list *env_list, char *name)
{
	t_env_node	*current;
	t_env_node	*previous;

	current = env_list->head;
	previous = NULL;
	while (current)
	{
		if (ft_strncmp(current->name, name,
				ft_strlen(name)) == 0
			&& ft_strlen(current->name) == ft_strlen(name))
		{
			if (previous)
				previous->next = current->next;
			else
				env_list->head = current->next;
			env_list->count--;
			break ;
		}
		previous = current;
		current = current->next;
	}
}

void	ft_unset(t_env_list *env_list, t_cmd_node *node)
{
	int			i;

	i = 1;
	while (node->cmd[i])
	{
		remove_env_var(env_list, node->cmd[i]);
		i++;
	}
	env_list->last_exitcode = 0;
}
