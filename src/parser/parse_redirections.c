/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:04:35 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/10 13:15:44 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Bestimmt den Redirection-Typ basierend auf Token
 * @param token_type Der Token-Typ
 * @return Entsprechender Redirection-Typ
 */
static int	get_redirection_type(t_token_type token_type)
{
	if (token_type == TOKEN_REDIR_IN)
		return (REDIR_IN);
	else if (token_type == TOKEN_REDIR_OUT)
		return (REDIR_OUT);
	else if (token_type == TOKEN_REDIR_APPEND)
		return (REDIR_APPEND);
	else if (token_type == TOKEN_REDIR_HEREDOC)
		return (REDIR_HEREDOC);
	//ft_putstr_fd("PARSER: Unexpected token type in get_redirection_type: ", 2);
	return (-1);
}

/**
 * @brief Entfernt Quotes von einem Delimiter und gibt bereinigten String zurück
 * @param delimiter Der quoted Delimiter
 * @return Bereinigter Delimiter ohne Quotes
 */
static char	*clean_quoted_delimiter(char *delimiter)
{
	int		len;
	char	*cleaned;

	if (!delimiter || !is_heredoc_delimiter_quoted(delimiter))
		return (gc_strdup(delimiter));
	len = ft_strlen(delimiter);
	cleaned = gc_substr(delimiter, 1, len - 2);
	return (cleaned);
}

/**
 * @brief Verarbeitet Heredoc-spezifische Logik
 * @param token Aktueller Token (sollte HEREDOC sein)
 * @param expand_vars Pointer auf expand_vars Flag
 * @return Bereinigter Delimiter für Heredoc
 */
static char	*process_heredoc_token(t_token *token, int *expand_vars)
{
	char	*delimiter;
	char	*cleaned_delimiter;

	if (!token->next || token->next->type != TOKEN_WORD)
		return (NULL);
	delimiter = token->next->value;
	if (is_heredoc_delimiter_quoted(delimiter))
	{
		*expand_vars = 0;
		cleaned_delimiter = clean_quoted_delimiter(delimiter);
	}
	else
	{
		*expand_vars = 1;
		cleaned_delimiter = gc_strdup(delimiter);
	}
	return (cleaned_delimiter);
}

/**
 * @brief Verarbeitet ein einzelnes Redirection-Token
 * @param token Aktueller Redirection-Token
 * @param cmd Command-Node zum Hinzufügen der Redirection
 * @return Nächster Token zum Verarbeiten
 */
static t_token	*process_single_redirection(t_token *token, t_cmd_node *cmd)
{
	t_file_node	*file;
	int			redir_type;
	int			expand_vars;
	char		*file_name;

	redir_type = get_redirection_type(token->type);
	expand_vars = 1;
	if (redir_type == REDIR_HEREDOC)
	{
		file_name = process_heredoc_token(token, &expand_vars);
		if (!file_name)
			return (error_handler("PARSER: Expected delimiter after <<", 0));
		token = token->next->next;
	}
	else
	{
		token = token->next;
		if (!token || token->type != TOKEN_WORD)
			return (error_handler("Expected filename after redirection", 0));
		file_name = gc_strdup(token->value);
		token = token->next;
	}
	file = create_file_node(file_name, redir_type);
	file->expand_vars = expand_vars;
	return (add_files_list(cmd->file, file), token);
}

/**
 * @brief Hauptfunktion zum Parsen aller Redirections
 * @param token Aktueller Token
 * @param cmd Command-Node
 * @return Nächster Token nach allen Redirections
 */
t_token	*parse_redirections(t_token *token, t_cmd_node *cmd)
{
	while (token && is_redirection_token(token->type))
	{
		token = process_single_redirection(token, cmd);
		if (!token)
			return (NULL);
	}
	return (token);
}
