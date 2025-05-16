/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:48 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/16 18:26:48 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		pipeline(t_env_list *env_list, t_cmd_node *node, pid_t *pids);
static void		child_process(t_cmd_node *node, int prev_fd,
					int *fd, t_env_list *env_list);
static void		parent_process(int *prev_fd, int *fd, int next);
static pid_t	safe_fork_command(t_cmd_node *node, int *fd);

void	execute(t_env_list *env_list, t_cmd_node *node)
{
	pid_t		*pids;
	int			cmd_count;
	int			prev_fd;
	int			child_count;
	int			i;

	prev_fd = -1;
	cmd_count = count_cmds(node);
	pids = gc_malloc(sizeof(pid_t) * cmd_count);
	child_count = pipeline(env_list, node, pids);
	if (prev_fd != -1)
		close(prev_fd);
	i = 0;
	while (i < child_count)
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}

static int	pipeline(t_env_list *env_list, t_cmd_node *node, pid_t *pids)
{
	t_cmd_node	*current;
	int			fd[2];
	int			prev_fd;
	pid_t		pid;
	int			i;

	current = node;
	i = 0;
	prev_fd = -1;
	while (current)
	{
		if (is_builtin(current))
			execute_builtin(current, env_list);
		else
		{
			pid = safe_fork_command(current, fd);
			if (pid == 0)
				child_process(current, prev_fd, fd, env_list);
			else
			{
				pids[i++] = pid;
				parent_process(&prev_fd, fd, current->next != NULL);
			}
		}
		current = current->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	return (i);
}

static pid_t	safe_fork_command(t_cmd_node *node, int *fd)
{
	pid_t	pid;

	if (node->next)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			clean_exit(1);
		}
	}
	else
	{
		fd[0] = -1;
		fd[1] = -1;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		clean_exit(1);
	}
	return (pid);
}

static	void	child_process(t_cmd_node *node, int prev_fd,
					int *fd, t_env_list *env_list)
{
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (fd[1] != -1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (node->file)
		execute_redirections(node->file);
	execute_external(node, env_list);
	exit(0);
}

static void	parent_process(int *prev_fd, int *fd, int next)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (next && fd[0] != -1 && fd[1] != -1)
	{
		close(fd[1]);
		*prev_fd = fd[0];
	}
}
