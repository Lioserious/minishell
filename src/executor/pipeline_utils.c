/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:51:22 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/26 09:56:02 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fork_execute_node(t_cmd_node *current,
				t_env_list *env_list, t_exec *context);
static void	execute_builtin_node(t_cmd_node *node, t_env_list *env_list);

int	execute_pipeline_loop(t_cmd_node *node,
				t_env_list *env_list, t_exec *context)
{
	t_cmd_node	*current;

	current = node;
	while (current)
	{
		if (is_builtin(current))
			execute_builtin_node(current, env_list);
		else
			fork_execute_node(current, env_list, context);
		current = current->next;
	}
	return (context->i);
}

static void	fork_execute_node(t_cmd_node *current,
				t_env_list *env_list, t_exec *context)
{
	pid_t	pid;
	int		fd[2];

	pid = fork();
	if (pid == 0)
	{
		child_process(current, context->prev_fd, fd, env_list);
		exit(0);
	}
	else
	{
		context->pids[context->i++] = pid;
		parent_process(&context->prev_fd, fd, current->next != NULL);
	}
}

static void	execute_builtin_node(t_cmd_node *node, t_env_list *env_list)
{
	if (node->file)
		execute_redirections(node->file);
	execute_builtin(node, env_list);
	restore_std_fds();
}
