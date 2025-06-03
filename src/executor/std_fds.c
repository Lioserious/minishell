/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:49:52 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/03 19:56:54 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_stdin_backup = -1;
static int	g_stdout_backup = -1;

void execute(t_env_list *env_list, t_cmd_node *node)
{
   pid_t *pids;
   int cmd_count;
   int prev_fd;
   int child_count;
   int i;

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
   signal(SIGINT, SIG_IGN);
   while (i < child_count)
   {
   	waitpid(pids[i], NULL, 0);
   	i++;
   }
   cleanup_heredocs(node);
   signal(SIGINT, main_sigint_handler);
   if (g_stdin_backup != -1 && g_stdout_backup != -1)
   	restore_std_fds();
}

void	restore_std_fds(void)
{
	if (g_stdin_backup == -1 || g_stdout_backup == -1)
		return ;
	if (dup2(g_stdin_backup, STDIN_FILENO) == -1
		|| dup2(g_stdout_backup, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		clean_exit(1);
	}
	close(g_stdin_backup);
	close(g_stdout_backup);
	g_stdin_backup = -1;
	g_stdout_backup = -1;
}

void	backup_std_fds(void)
{
	g_stdin_backup = dup(STDIN_FILENO);
	g_stdout_backup = dup(STDOUT_FILENO);
	if (g_stdin_backup == -1 || g_stdout_backup == -1)
	{
		perror("dup");
		clean_exit(1);
	}
}
