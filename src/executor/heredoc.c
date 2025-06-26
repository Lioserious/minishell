/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 08:36:19 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/11 18:45:53 by mimalek          ###   ########.fr       */
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

static int	read_heredoc_loop(t_file_node *file,
				t_env_list *env_list, int write_fd)
{
	char	*line;

	while (!g_heredoc)
	{
		line = readline("> ");
		if (g_heredoc)
		{
			if (line)
				free(line);
			break ;
		}
		if (!line)
			break ;
		if (should_end_heredoc(line, file->name))
		{
			free(line);
			break ;
		}
		process_and_write_line(line, file, env_list, write_fd);
		free(line);
	}
	if (g_heredoc)
		return (1);
	return (0);
}

void	read_heredoc_lines(t_file_node *file, t_env_list *env_list, int pipe_fd)
{
	int		original_stdin_fd;

	original_stdin_fd = dup(STDIN_FILENO);
	if (original_stdin_fd == -1)
	{
		perror("dup original_stdin_fd");
		close(pipe_fd);
		return ;
	}
	g_heredoc = 0;
	if (read_heredoc_loop(file, env_list, pipe_fd))
		file->heredoc_fd = -1;
	close(pipe_fd);
	if (dup2(original_stdin_fd, STDIN_FILENO) == -1)
	{
		perror("dup2 original_stdin-fd after heredoc");
		clean_exit(env_list);
	}
	close(original_stdin_fd);
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
