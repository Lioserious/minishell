/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:30:29 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/22 16:10:10 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_fd(char *filename, int flags, int std);

void	execute_redirections(t_file_list *file_list)
{
	t_file_node	*current_file;

	current_file = file_list->head;
	while (current_file)
	{
		if (current_file->redirection_type == REDIR_IN)
			redirect_fd(current_file->name, O_RDONLY, STDIN_FILENO);
		else if (current_file->redirection_type == REDIR_OUT)
			redirect_fd(current_file->name, O_WRONLY | O_CREAT
				| O_TRUNC, STDOUT_FILENO);
		else if (current_file->redirection_type == REDIR_APPEND)
			redirect_fd(current_file->name, O_WRONLY | O_CREAT
				| O_APPEND, STDOUT_FILENO);
		else if (current_file->redirection_type == REDIR_HEREDOC)
		{
			if (dup2(current_file->heredoc_fd, STDIN_FILENO) == -1)
			{
				perror("heredoc dup2");
				clean_exit(1);
			}
			close(current_file->heredoc_fd);
		}
		current_file = current_file->next;
	}
}

static void	redirect_fd(char *filename, int flags, int std)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror(filename);
		clean_exit(1);
	}
	if (dup2(fd, std) == -1)
	{
		perror("dup2");
		close(fd);
		clean_exit(1);
	}
	close(fd);
}

void	setup_heredoc(t_file_node *file)
{
	char	*line;
	int		heredoc_pipe[2];

	if (pipe(heredoc_pipe) == -1)
	{
		perror("pipe");
		clean_exit(1);
	}
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, file->name) == 0)
		{
			free(line);
			break ;
		}
		write(heredoc_pipe[1], line, ft_strlen(line));
		write(heredoc_pipe[1], "\n", 1);
		free(line);
	}
	close(heredoc_pipe[1]);
	file->heredoc_fd = heredoc_pipe[0];
}
