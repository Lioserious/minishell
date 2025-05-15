/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:48 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/15 10:38:28 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	child_process(t_cmd_node *node, int prev_fd, int *fd, t_env_list *env_list);
static	void	parent_process(pid_t pid, int *prev_fd, int *fd, int next);

void	execute(t_env_list *env_list, t_cmd_node *node)
{
	t_cmd_node	*current;
	int			fd[2];
	int			prev_fd = -1;
	pid_t		pid;

	current = node;
	while (current)
	{
		if (current->next && pipe(fd) == -1)
		{
			clean_exit();
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		pid = fork();
		if (pid == -1)
		{
			clean_exit();
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
			child_process(current, prev_fd, fd, env_list);
		else
			parent_process(pid, &prev_fd, fd, current->next != NULL);
		current = current->next;
	}
}

static	void	child_process(t_cmd_node *node, int prev_fd, int *fd, t_env_list *env_list)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (node->next)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (node->file)
		execute_redirections(node->file);
	if (node->cmd_type == CMD_BUILTIN)
		execute_builtin(node, env_list);
	else
		execute_external(node, env_list);
	clean_exit();
}

static void	parent_process(pid_t pid, int *prev_fd, int *fd, int next)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (next)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
	waitpid(pid, NULL, 0);
}
