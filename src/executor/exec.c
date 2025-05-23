/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:48 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/22 16:49:55 by mimalek          ###   ########.fr       */
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
	if (child_count == 0)
	{
		g_heredoc = 0;
		return ;
	}
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
	int			stdin;
	int			stdout;
	t_file_node	*file;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	current = node;
	while (current)
	{
		if (current->file)
		{
			file = current->file->head;
			while (file)
			{
				if (file->redirection_type == REDIR_HEREDOC)
					setup_heredoc(file);
				file = file->next;
			}
			current = current->next;
		}
	}
	if (heredoc_interupt(node))
		return (0);
	current = node;
	i = 0;
	prev_fd = -1;
	while (current)
	{
		if (is_builtin(current))
		{
			if (current->file)
				execute_redirections(node->file);
			execute_builtin(current, env_list);
			dup2(stdin, STDIN_FILENO);
			dup2(stdout, STDOUT_FILENO);
			close(stdin);
			close(stdout);
		}
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
