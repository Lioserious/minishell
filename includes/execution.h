/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:50:45 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/26 09:03:04 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "env.h"
# include <stdbool.h>

void	execute(t_env_list *env_list, t_cmd_node *node);
void	execute_builtin(t_cmd_node *node, t_env_list *env_list);
void	execute_external(t_cmd_node *node, t_env_list *env_list);
void	execute_redirections(t_file_list *file_list);
int		count_cmds(t_cmd_node *node);
int		is_builtin(t_cmd_node *node);
pid_t	safe_fork_command(t_cmd_node *node, int *fd);
int		heredoc_interupt(t_cmd_node *node);
int		init_heredoc_pipe(int *heredoc_pipe);
void	read_heredoc_lines(t_file_node *file, t_env_list *env_list, int pipe_fd);
void	finalize_heredoc_pipe(t_file_node *file, int *heredoc_pipe);
char	*expand_heredoc_line(char *line, t_env_list *env_list);
void	setup_heredoc_no_signals(t_file_node *file, t_env_list *env_list);
void	cleanup_heredocs(t_cmd_node *node);
void	process_and_write_line(char *line, t_file_node *file,
	t_env_list *env_list, int pipe_fd);
int		should_end_heredoc(char *line, char *delimiter);
#endif
