/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:04:35 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/16 16:56:42 by lihrig           ###   ########.fr       */
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
 * @brief Validiert einen Heredoc-Delimiter
 * @param delimiter Der zu validierende Delimiter
 * @return 1 wenn gültig, 0 wenn ungültig
 */
static int	validate_heredoc_delimiter(char *delimiter)
{
	char	*cleaned;
	int		len;

	if (!delimiter)
		return (0);
	len = ft_strlen(delimiter);
	if (len == 0)
		return (0);
	if ((len == 2 && delimiter[0] == '"' && delimiter[1] == '"') || (len == 2
			&& delimiter[0] == '\'' && delimiter[1] == '\''))
		return (0);
	if (is_heredoc_delimiter_quoted(delimiter))
	{
		if (len < 3)
			return (0);
		cleaned = clean_quoted_delimiter(delimiter);
		return (cleaned && cleaned[0] != '\0');
	}
	return (1);
}

/**
 * @brief Verarbeitet Heredoc-spezifische Logik
 * @param token Aktueller Token (sollte HEREDOC sein)
 * @param expand_vars Pointer auf expand_vars Flag
 * @param env_list Environment list for exit code
 * @return Bereinigter Delimiter für Heredoc
 */
static char	*process_heredoc_token(t_token *token, int *expand_vars,
		t_env_list *env_list)
{
	char	*delimiter;
	char	*cleaned_delimiter;

	if (!token->next || token->next->type != TOKEN_WORD)
	{
		if (env_list)
			env_list->last_exitcode = 2;
		return (error_handler("syntax error near unexpected token `newline'",
				0));
	}
	delimiter = token->next->value;
	if (!validate_heredoc_delimiter(delimiter))
	{
		if (env_list)
			env_list->last_exitcode = 2;
		return (error_handler("syntax error: empty heredoc delimiter", 0));
	}
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
 * @param env_list Environment list for exit code
 * @return Nächster Token zum Verarbeiten
 */
static t_token	*process_single_redirection(t_token *token, t_cmd_node *cmd,
		t_env_list *env_list)
{
	t_file_node	*file;
	int			redir_type;
	int			expand_vars;
	char		*file_name;

	redir_type = get_redirection_type(token->type);
	expand_vars = 1;
	if (redir_type == REDIR_HEREDOC)
	{
		file_name = process_heredoc_token(token, &expand_vars, env_list);
		if (!file_name)
			return (NULL);
		token = token->next->next;
	}
	else
	{
		token = token->next;
		if (!token || token->type != TOKEN_WORD)
		{
			if (env_list)
				env_list->last_exitcode = 2;
			error_handler("syntax error near unexpected token `newline'", 0);
			return (NULL);
		}
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
