/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:51:22 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/03 14:33:24 by mimalek          ###   ########.fr       */
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
	int			cmd_count;

	current = node;
	cmd_count = count_cmds(node);
	if (cmd_count == 1 && is_builtin(current))
	{
		execute_builtin_node(current, env_list);
		return (0);
	}
	while (current)
	{
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

	if (current->next)
	{
		if (pipe(fd) == -1)
			clean_exit(1);
	}
	else
	{
		fd[0] = -1;
		fd[1] = -1;
	}
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
	int	stdin;
	int	stdout;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	if (stdin == -1 || stdout == -1)
	{
		perror("dup");
		clean_exit(1);
	}
	if (node->file)
		execute_redirections(node->file);
	if (ft_strcmp(node->cmd[0], "exit") == 0)
	{
		close(stdin);
		close(stdout);
		ft_exit(node);
	}
	execute_builtin(node, env_list);
	if (dup2(stdin, STDIN_FILENO) == -1
		|| dup2(stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		clean_exit(1);
	}
	close(stdin);
	close(stdout);
}
