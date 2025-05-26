/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   std_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 09:49:52 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/26 10:07:30 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	g_stdin_backup;
static int	g_stdout_backup;

void	restore_std_fds(void)
{
	if (dup2(g_stdin_backup, STDIN_FILENO) == -1
		|| dup2(g_stdout_backup, STDOUT_FILENO) == -1)
	{
		perror("dup2");
		clean_exit(1);
	}
	close(g_stdin_backup);
	close(g_stdout_backup);
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
