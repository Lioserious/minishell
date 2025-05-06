/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 12:18:21 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/06 12:52:23 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(t_env_list *env_list, t_cmd_node *node)
{
	t_env_node	*current;
	t_env_node	*previous;
	int			i;

	i = 1;
	while (node->cmd[i])
	{
		current = env_list->head;
		previous = NULL;
		while (current)
		{
			if (ft_strncmp(current->name, node->cmd[i], ft_strlen(node->cmd[i])) == 0
			&& ft_strlen(current->name) == ft_strlen(node->cmd[i]))
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
		i++;
	}
	return (0);
}
