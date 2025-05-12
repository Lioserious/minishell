/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:58:35 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/12 14:19:04 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

// helper
int		is_redirection_token(t_token_type type);
char	**realloc_cmd_args(char **args, int new_size);
void	print_parsed_cmd_list(t_cmd_list *cmd_list)
t_token *parse_redirections(t_token *token, t_cmd_node *cmd);

#endif
