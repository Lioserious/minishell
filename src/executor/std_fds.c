/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:49:52 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/08 14:47:13 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wait_children_set_exitcode(pid_t *pids, int child_count,
				t_env_list *env_list);

static int	g_stdin_backup = -1;
static int	g_stdout_backup = -1;

void	execute(t_env_list *env_list, t_cmd_node *node)
{
	pid_t	*pids;
	int		cmd_count;
	int		prev_fd;
	int		child_count;

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
	signal(SIGINT, SIG_IGN);
	wait_children_set_exitcode(pids, child_count, env_list);
	cleanup_heredocs(node);
	signal(SIGINT, main_sigint_handler);
	if (g_stdin_backup != -1 && g_stdout_backup != -1)
		restore_std_fds(env_list);
}

static void	wait_children_set_exitcode(pid_t *pids, int child_count,
										t_env_list *env_list)
{
	int	i;
	int	status;

	i = 0;
	while (i < child_count)
	{
		waitpid(pids[i], &status, 0);
		if (WIFEXITED(status))
			env_list->last_exitcode = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			env_list->last_exitcode = 128 + WTERMSIG(status);
		i++;
	}
}

void	restore_std_fds(t_env_list *env_list)
{
	if (g_stdin_backup == -1 || g_stdout_backup == -1)
		return ;
	if (dup2(g_stdin_backup, STDIN_FILENO) == -1
		|| dup2(g_stdout_backup, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		env_list->last_exitcode = 1;
		clean_exit(env_list);
	}
	close(g_stdin_backup);
	close(g_stdout_backup);
	g_stdin_backup = -1;
	g_stdout_backup = -1;
}

void	backup_std_fds(t_env_list *env_list)
{
	g_stdin_backup = dup(STDIN_FILENO);
	g_stdout_backup = dup(STDOUT_FILENO);
	if (g_stdin_backup == -1 || g_stdout_backup == -1)
	{
		perror("dup");
		env_list->last_exitcode = 1;
		clean_exit(env_list);
	}
}
