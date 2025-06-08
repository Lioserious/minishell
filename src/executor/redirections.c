/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/13 09:30:29 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/08 14:12:07 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_redirection(t_file_node *file, t_env_list *env_list);
static void	redirect_fd(char *filename, int flags,
				int std, t_env_list *env_list);

void	execute_redirections(t_file_list *file_list, t_env_list *env_list)
{
	t_file_node	*current_file;

	current_file = file_list->head;
	while (current_file)
	{
		handle_redirection(current_file, env_list);
		current_file = current_file->next;
	}
}

static void	handle_redirection(t_file_node *file, t_env_list *env_list)
{
	if (file->redirection_type == REDIR_IN)
		redirect_fd(file->name, O_RDONLY, STDIN_FILENO, env_list);
	else if (file->redirection_type == REDIR_OUT)
		redirect_fd(file->name, O_WRONLY | O_CREAT | O_TRUNC,
			STDOUT_FILENO, env_list);
	else if (file->redirection_type == REDIR_APPEND)
		redirect_fd(file->name, O_WRONLY | O_CREAT | O_APPEND,
			STDOUT_FILENO, env_list);
	else if (file->redirection_type == REDIR_HEREDOC)
	{
		if (file->heredoc_fd == -1)
			clean_exit(env_list);
		if (dup2(file->heredoc_fd, STDIN_FILENO) == -1)
		{
			perror("heredoc dup2");
			env_list->last_exitcode = 1;
			clean_exit(env_list);
		}
		close(file->heredoc_fd);
	}
}

static void	redirect_fd(char *filename, int flags,
						int std, t_env_list *env_list)
{
	int	fd;

	fd = open(filename, flags, 0644);
	if (fd == -1)
	{
		perror(filename);
		env_list->last_exitcode = 1;
		clean_exit(env_list);
	}
	if (dup2(fd, std) == -1)
	{
		perror("dup2");
		close(fd);
		env_list->last_exitcode = 1;
		clean_exit(env_list);
	}
	close(fd);
}
