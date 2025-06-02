/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:36:19 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/02 13:48:08 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//static int	redirect_stdout_to_tty(void);

void	setup_heredoc_no_signals(t_file_node *file, t_env_list *env_list)
{
	int	heredoc_pipe[2];

	if (init_heredoc_pipe(heredoc_pipe) == -1)
		return ;
	read_heredoc_lines(file, env_list, heredoc_pipe[1]);
	finalize_heredoc_pipe(file, heredoc_pipe);
}

void	read_heredoc_lines(t_file_node *file, t_env_list *env_list, int pipe_fd)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			if (errno == EINTR)
				continue;
			break;
		}
		if (should_end_heredoc(line, file->name))
		{
			free(line);
			break ;
		}
		process_and_write_line(line, file, env_list, pipe_fd);
		free(line);
	}
	close(pipe_fd);
}

// static int	redirect_stdout_to_tty(void)
// {
// 	int		tty_fd;
// 	int		backup_stdout;

// 	backup_stdout = dup(STDOUT_FILENO);
// 	if (backup_stdout == -1)
// 	{
// 		perror("dup");
// 		clean_exit(1);
// 	}
// 	tty_fd = open("/dev/tty", O_RDWR);
// 	if (tty_fd == -1)
// 	{
// 		perror("open /dev/tty");
// 		close(backup_stdout);
// 		return (-1);
// 	}
// 	if (dup2(tty_fd, STDOUT_FILENO) == -1)
// 	{
// 		perror("dup2");
// 		close(backup_stdout);
// 		close(tty_fd);
// 		return (-1);
// 	}
// 	close(tty_fd);
// 	return (backup_stdout);
// }

void	cleanup_heredocs(t_cmd_node *node)
{
	t_cmd_node	*current;
	t_file_node	*file;

	current = node;
	while (current)
	{
		if (current->file)
		{
			file = current->file->head;
			while (file)
			{
				if (file->redirection_type == REDIR_HEREDOC
					&& file->heredoc_fd != -1)
				{
					close(file->heredoc_fd);
					file->heredoc_fd = -1;
				}
				file = file->next;
			}
		}
		current = current->next;
	}
}

int	heredoc_interupt(t_cmd_node *node)
{
	t_cmd_node	*cmd;
	t_file_node	*file;

	cmd = node;
	while (cmd)
	{
		if (cmd->file)
			file = cmd->file->head;
		else
			file = NULL;
		while (file)
		{
			if (file->redirection_type == REDIR_HEREDOC
				&& file->heredoc_fd == -1)
				return (1);
			file = file->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
