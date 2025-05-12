/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:04:55 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/12 14:57:17 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*parse_redirections(t_token *token, t_cmd_node *cmd)
{
	t_file_node	*file;
	int			redir_type;

	while (token && is_redirection_token(token->type))
	{
		if (token->type == TOKEN_REDIR_IN)
			redir_type = REDIR_IN;
		else if (token->type == TOKEN_REDIR_OUT)
			redir_type = REDIR_OUT;
		else if (token->type == TOKEN_REDIR_APPEND)
			redir_type = REDIR_APPEND;
		else if (token->type == TOKEN_REDIR_HEREDOC)
			redir_type = REDIR_HEREDOC;
		token = token->next;
		if (!token || token->type != TOKEN_WORD)
			return (error_handler("PARSER: Expected filename after redirection",
					1), NULL);
		file = create_file_node(token->value, redir_type);
		add_files_list(cmd->file, file);
		token = token->next;
	}
	return (token);
}
// Diese Funktion wird später implementiert
// Hier nur ein Platzhalter, um Kompilierungsfehler zu vermeiden
t_token	*parse_simple_command(t_token *token, t_cmd_list *cmd_list)
{
	t_cmd_node	*cmd;
	char		**cmd_array;
	int			arg_count;

	cmd_array = NULL;
	arg_count = 0;
	// Hier die Bedingung anpassen, um TOKEN_ENV_VAR zu akzeptieren
	while (token && (token->type == TOKEN_WORD || token->type == TOKEN_ENV_VAR)
		&& !is_redirection_token(token->type) && token->type != TOKEN_PIPE
		&& token->type != TOKEN_EOF)
	{
		cmd_array = realloc_cmd_args(cmd_array, arg_count + 1);
		cmd_array[arg_count] = gc_strdup(token->value);
		arg_count++;
		token = token->next;
	}
	if (arg_count > 0)
	{
		cmd = create_cmd_node(cmd_array, CMD_SIMPLE);
		token = parse_redirections(token, cmd);
		add_cmd_to_list(cmd_list, cmd);
	}
	return (token);
}

t_cmd_list	*parser(t_token_list *token_list)
{
	t_cmd_list	*cmd_list;
	t_token		*current_token;

	if (!token_list || !token_list->head)
		return (NULL);
	cmd_list = create_cmd_list();
	current_token = token_list->head;
	while (current_token && current_token->type != TOKEN_EOF)
	{
		if (!current_token->value || current_token->value[0] == '\0')
		{
			current_token = current_token->next;
			continue ;
		}
		current_token = parse_simple_command(current_token, cmd_list);
		if (!current_token)
			return (cmd_list);
		if (current_token)
			current_token = current_token->next;
	}
	if (cmd_list->size == 0)
		return (error_handler("PARSER: NO VALID COMMAND", 0), cmd_list);
	return (cmd_list);
}
