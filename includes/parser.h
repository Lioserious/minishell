/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:58:35 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/02 14:46:36 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "minishell.h"
// helper
int			is_empty_token(t_token *token);
int			validate_start_token(t_token_list *token_list);
int			pipe_syntax_error(void);
int			validate_token_sequence(t_token_list *token_list);
int			is_redirection_token(t_token_type type);
char		**realloc_cmd_args(char **args, int new_size);
void		print_parsed_cmd_list(t_cmd_list *cmd_list);
void		add_files_list(t_file_list *list, t_file_node *node);
t_token		*parse_redirections(t_token *token, t_cmd_node *cmd);
t_cmd_list	*parser(t_token_list *token_list);
int			is_builtin_command(char *cmd);
// test
void		run_env_var_tests(void);
void		run_parser_tests(void);

#endif
