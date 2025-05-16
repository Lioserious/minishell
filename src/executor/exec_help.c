/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:44:02 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/15 11:44:22 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_cmd_node *node)
{
	t_cmd_node	*current;
	int			count;

	count = 0;
	current = node;
	while (current)
	{
		count++;
		current = current -> next;
	}
	return (count);
}
