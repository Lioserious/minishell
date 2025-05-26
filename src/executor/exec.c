/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:48 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/26 09:04:36 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		pipeline(t_env_list *env_list, t_cmd_node *node, pid_t *pids);
static void		child_process(t_cmd_node *node, int prev_fd,
					int *fd, t_env_list *env_list);
static void		parent_process(int *prev_fd, int *fd, int next);

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
	t_cmd_node			*current;
	int					fd[2];
	int					prev_fd;
	pid_t				pid;
	int					i;
	int					stdin;
	int					stdout;
	t_file_node			*file;
	struct sigaction	sa_old;
	struct sigaction	sa_new;

	stdin = dup(STDIN_FILENO);
	stdout = dup(STDOUT_FILENO);
	g_heredoc = 0;
	sa_new.sa_handler = heredoc_signal_handler;
	sigemptyset(&sa_new.sa_mask);
	sa_new.sa_flags = 0;
	sigaction(SIGINT, &sa_new, &sa_old);
	signal(SIGQUIT, SIG_IGN);
	current = node;
	while (current && !g_heredoc)
	{
		if (current->file)
		{
			file = current->file->head;
			while (file && !g_heredoc)
			{
				if (file->redirection_type == REDIR_HEREDOC)
					setup_heredoc_no_signals(file, env_list);
				file = file->next;
			}
		}
		current = current->next;
	}
	sigaction(SIGINT, &sa_old, NULL);
	signal(SIGQUIT, SIG_DFL);
	if (g_heredoc)
	{
		cleanup_heredocs(node);
		if (dup2(stdin, STDIN_FILENO) == -1)
		{
			perror("dup2 stdin restore");
			clean_exit(1);
		}
		close(stdin);
		close(stdout);
		return (0);
	}
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
	close(stdin);
	close(stdout);
	if (prev_fd != -1)
		close(prev_fd);
	return (i);
}

static	void	child_process(t_cmd_node *node, int prev_fd,
					int *fd, t_env_list *env_list)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
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
