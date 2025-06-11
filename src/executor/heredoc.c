/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:36:19 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/11 15:56:54 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	setup_heredoc_no_signals(t_file_node *file, t_env_list *env_list)
{
	int	heredoc_pipe[2];

	if (init_heredoc_pipe(heredoc_pipe, env_list) == -1)
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
				continue ;
			break ;
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
