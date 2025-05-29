/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:48 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/29 14:56:37 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		setup_all_heredocs(t_env_list *env_list, t_cmd_node *node);

int	pipeline(t_env_list *env_list, t_cmd_node *node, pid_t *pids)
{
	int		i;
	t_exec	context;

	backup_std_fds();
	if (setup_all_heredocs(env_list, node))
	{
		cleanup_heredocs(node);
		return (0);
	}
	context.prev_fd = -1;
	context.i = 0;
	context.pids = pids;
	i = execute_pipeline_loop(node, env_list, &context);
	restore_std_fds();
	return (i);
}

static int	setup_all_heredocs(t_env_list *env_list, t_cmd_node *node)
{
	t_cmd_node	*current;
	t_file_node	*file;

	g_heredoc = 0;
	handle_heredoc_signals();
	current = node;
	while (current && !g_heredoc)
	{
		if (current->file)
			file = current->file->head;
		else
			file = NULL;
		while (file && !g_heredoc)
		{
			if (file->redirection_type == REDIR_HEREDOC)
				setup_heredoc_no_signals(file, env_list);
			file = file->next;
		}
		current = current->next;
	}
	restore_signals();
	return (g_heredoc);
}

void	child_process(t_cmd_node *node, int prev_fd,
					int *fd, t_env_list *env_list)
{
	char	**enva;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (fd[1] != -1)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
	}
	if (node->file)
		execute_redirections(node->file);
	if (is_builtin(node))
	{
		execute_builtin(node, env_list);
		exit(0);
	}
	enva = convert_env_struct_array(env_list);
	handle_child_process(node, env_list, enva);
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
