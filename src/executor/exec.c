/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:48 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/13 10:58:46 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(t_env_list *env_list, t_cmd_node *node)
{
	int	stdin;
	int	stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);

	if (node->file)
	{
		execute_redirections(node->file);
	}
	if (node->cmd_type == CMD_BUILTIN)
	{
		execute_builtin(node, env_list);
	}
	else if (node->cmd_type == CMD_SIMPLE)
	{
		execute_external(node, env_list);
	}
	dup2(stdin, STDIN_FILENO);
	dup2(stdout, STDOUT_FILENO);
	close(stdin);
	close(stdout);
}
