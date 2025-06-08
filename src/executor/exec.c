/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:48 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/08 14:50:11 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		setup_child_io_and_redirs(t_cmd_node *node, int prev_fd,
					int *fd, t_env_list *env_list);
static void		process_heredoc_in_node(t_cmd_node *current,
					t_env_list *env_list,
					t_file_node **last_heredoc,
					int *heredoc_count);

static void	process_heredoc_in_node(t_cmd_node *current,
									t_env_list *env_list,
									t_file_node **last_heredoc,
									int *heredoc_count)
{
	t_file_node	*file;

	file = current->file->head;
	while (file)
	{
		if (file->redirection_type == REDIR_HEREDOC)
		{
			(*heredoc_count)++;
			if (*last_heredoc && (*last_heredoc)->heredoc_fd != -1)
			{
				close((*last_heredoc)->heredoc_fd);
				(*last_heredoc)->heredoc_fd = -1;
			}
			setup_heredoc_no_signals(file, env_list);
			*last_heredoc = file;
		}
		file = file->next;
	}
}

int	setup_all_heredocs(t_env_list *env_list, t_cmd_node *node)
{
	t_cmd_node	*current;
	t_file_node	*last_heredoc;
	int			heredoc_count;

	heredoc_count = 0;
	last_heredoc = NULL;
	setup_heredoc_signal_handling();
	current = node;
	while (current)
	{
		process_heredoc_in_node(current, env_list,
			&last_heredoc, &heredoc_count);
		current = current->next;
	}
	restore_main_signals();
	return (0);
}

static void	setup_child_io_and_redirs(t_cmd_node *node, int prev_fd,
										int *fd, t_env_list *env_list)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_fd != -1)
	{
		if (dup2(prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 stdin");
			exit(1);
		}
		close(prev_fd);
	}
	if (fd[1] != -1)
	{
		close(fd[0]);
		if (dup2(fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 stdout");
			exit(1);
		}
		close(fd[1]);
	}
	if (node->file)
		execute_redirections(node->file, env_list);
}

void	child_process(t_cmd_node *node, int prev_fd,
						int *fd, t_env_list *env_list)
{
	char	**enva;

	setup_child_io_and_redirs(node, prev_fd, fd, env_list);
	if (is_builtin(node))
	{
		execute_builtin(node, env_list);
		exit(0);
	}
	else
	{
		enva = convert_env_struct_array(env_list);
		handle_child_process(node, env_list, enva);
	}
}

void	parent_process(int *prev_fd, int *fd, int next)
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (fd[1] != -1)
		close(fd[1]);
	if (next && fd[0] != -1)
		*prev_fd = fd[0];
	else if (fd[0] != -1)
	{
		close(fd[0]);
		*prev_fd = -1;
	}
}
