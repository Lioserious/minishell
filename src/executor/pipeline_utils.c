/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:51:22 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/26 16:49:19 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fork_execute_node(t_cmd_node *current,
				t_env_list *env_list, t_exec *context);
static void	execute_builtin_node(t_cmd_node *node, t_env_list *env_list);
static void	backup_std_fds_exit(int *stdin_fd, int *stdout_fd,
				t_env_list *env_list);

int	execute_pipeline_loop(t_cmd_node *node,
				t_env_list *env_list, t_exec *context)
{
	t_cmd_node	*current;
	int			cmd_count;

	current = node;
	cmd_count = count_cmds(node);
	if (cmd_count == 1 && is_builtin(current))
	{
		if (has_heredoc(current))
		{
			fork_execute_node(current, env_list, context);
			return (1);
		}
		else
		{
			execute_builtin_node(current, env_list);
			return (0);
		}
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
			clean_exit(env_list);
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

static void	backup_std_fds_exit(int *stdin_fd, int *stdout_fd,
								t_env_list *env_list)
{
	*stdin_fd = dup(STDIN_FILENO);
	*stdout_fd = dup(STDOUT_FILENO);
	if (*stdin_fd == -1 || *stdout_fd == -1)
	{
		perror("dup");
		env_list->last_exitcode = 1;
		clean_exit(env_list);
	}
}

static void	execute_builtin_node(t_cmd_node *node, t_env_list *env_list)
{
	int	stdin;
	int	stdout;

	backup_std_fds_exit(&stdin, &stdout, env_list);
	if (node->file)
		execute_redirections(node->file, env_list);
	if (ft_strcmp(node->cmd[0], "exit") == 0)
	{
		ft_exit(node, env_list, stdin, stdout);
	}
	execute_builtin(node, env_list);
	if (dup2(stdin, STDIN_FILENO) == -1
		|| dup2(stdout, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		env_list->last_exitcode = 1;
		clean_exit(env_list);
	}
	close(stdin);
	close(stdout);
}
