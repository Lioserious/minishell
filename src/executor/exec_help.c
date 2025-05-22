/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_help.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:44:02 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/22 16:08:48 by mimalek          ###   ########.fr       */
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

int	is_builtin(t_cmd_node *node)
{
	char	*cmd;

	cmd = node->cmd[0];
	return (ft_strcmp(cmd, "exit") == 0
		|| ft_strcmp(cmd, "cd") == 0
		|| ft_strcmp(cmd, "echo") == 0
		|| ft_strcmp(cmd, "export") == 0
		|| ft_strcmp(cmd, "unset") == 0
		|| ft_strcmp(cmd, "env") == 0
		|| ft_strcmp(cmd, "pwd") == 0);
}
