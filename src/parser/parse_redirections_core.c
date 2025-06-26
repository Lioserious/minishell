/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections_core.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 18:46:57 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/26 12:46:32 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Bestimmt den Redirection-Typ basierend auf Token
 * @param token_type Der Token-Typ
 * @return Entsprechender Redirection-Typ
 */
int	get_redirection_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	else if (token_type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	else if (token_type == TOKEN_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	return (-1);
}

/**
 * @brief Verarbeitet Heredoc-Redirection
 * @param token Aktueller Token
 * @param expand_vars Pointer auf expand_vars Flag
 * @param env_list Environment list for exit code
 * @return Filename und nächster Token
 */
t_token	*process_heredoc_redirection(t_token *token, char **file_name,
		int *expand_vars, t_env_list *env_list)
{
	*file_name = process_heredoc_token(token, expand_vars, env_list);
	if (!*file_name)
		return (NULL);
	return (token->next->next);
}

/**
 * @brief Verarbeitet Standard-Redirection (nicht Heredoc)
 * @param token Aktueller Token
 * @param file_name Pointer auf filename
 * @param env_list Environment list for exit code
 * @return Nächster Token oder NULL bei Fehler
 */
t_token	*process_standard_redirection(t_token *token, char **file_name,
		t_env_list *env_list)
{
	token = token->next;
	if (!token || token->type != TOKEN_WORD)
	{
		if (env_list)
			env_list->last_exitcode = 2;
		error_handler("syntax error near unexpected token `newline'", 0);
		return (NULL);
	}
	*file_name = gc_strdup(token->value);
	return (token->next);
}

/**
 * @brief Verarbeitet ein einzelnes Redirection-Token
 * @param token Aktueller Redirection-Token
 * @param cmd Command-Node zum Hinzufügen der Redirection
 * @param env_list Environment list for exit code
 * @return Nächster Token zum Verarbeiten
 */
t_token	*process_single_redirection(t_token *token, t_cmd_node *cmd,
		t_env_list *env_list)
{
	t_file_node	*file;
	int			redir_type;
	int			expand_vars;
	char		*file_name;

	redir_type = get_redirection_type(token->type);
	expand_vars = 1;
	if (redir_type == REDIR_HEREDOC)
		token = process_heredoc_redirection(token, &file_name, &expand_vars,
				env_list);
	else
		token = process_standard_redirection(token, &file_name, env_list);
	if (!token)
		return (NULL);
	file = create_file_node(file_name, redir_type);
	file->expand_vars = expand_vars;
	return (add_files_list(cmd->file, file), token);
}

/**
 * @brief Hauptfunktion zum Parsen aller Redirections
 * @param token Aktueller Token
 * @param cmd Command-Node
 * @param env_list Environment list for exit code
 * @return Nächster Token nach allen Redirections
 */
t_token	*parse_redirections(t_token *token, t_cmd_node *cmd,
		t_env_list *env_list)
{
	while (token && is_redirection_token(token->type))
	{
		token = process_single_redirection(token, cmd, env_list);
		if (!token)
			return (NULL);
	}
	return (token);
}
