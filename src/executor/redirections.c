/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:30:29 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/13 10:12:59 by mimalek          ###   ########.fr       */
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
			redirect_fd(current_file->name, O_WRONLY | O_CREAT | O_TRUNC, STDOUT_FILENO);
		else if (current_file->redirection_type == REDIR_APPEND)
			redirect_fd(current_file->name, O_WRONLY | O_CREAT | O_APPEND, STDOUT_FILENO);
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
		exit(EXIT_FAILURE);
	}
	if (dup2(fd, std) == -1)
	{
		perror("dup2");
		close(fd);
		exit(EXIT_FAILURE);
	}
	close(fd);
}
