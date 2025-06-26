/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:04:35 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/26 12:47:25 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Entfernt Quotes von einem Delimiter und gibt bereinigten String zurück
 * @param delimiter Der quoted Delimiter
 * @return Bereinigter Delimiter ohne Quotes
 */
char	*clean_quoted_delimiter(char *delimiter)
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
 * @brief Prüft ob ein Delimiter leer oder nur Quotes enthält
 * @param delimiter Der zu prüfende Delimiter
 * @param len Die Länge des Delimiters
 * @return 1 wenn leer, 0 wenn gültig
 */
int	is_empty_delimiter(char *delimiter, int len)
{
	if (len == 0)
		return (1);
	if ((len == 2 && delimiter[0] == '"' && delimiter[1] == '"') || (len == 2
			&& delimiter[0] == '\'' && delimiter[1] == '\''))
		return (1);
	return (0);
}

/**
 * @brief Validiert einen Heredoc-Delimiter
 * @param delimiter Der zu validierende Delimiter
 * @return 1 wenn gültig, 0 wenn ungültig
 */
int	validate_heredoc_delimiter(char *delimiter)
{
	int	len;

	if (!delimiter)
		return (0);
	len = ft_strlen(delimiter);
	if (is_empty_delimiter(delimiter, len))
		return (0);
	if (is_heredoc_delimiter_quoted(delimiter))
		return (validate_quoted_delimiter(delimiter, len));
	return (1);
}

/**
 * @brief Validiert und verarbeitet Heredoc-Delimiter-Token
 * @param token Der Heredoc-Token
 * @param env_list Environment list for exit code
 * @return Delimiter-String oder NULL bei Fehler
 */
char	*get_heredoc_delimiter(t_token *token, t_env_list *env_list)
{
	char	*delimiter;

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
	return (delimiter);
}

/**
 * @brief Verarbeitet Heredoc-spezifische Logik
 * @param token Aktueller Token (sollte HEREDOC sein)
 * @param expand_vars Pointer auf expand_vars Flag
 * @param env_list Environment list for exit code
 * @return Bereinigter Delimiter für Heredoc
 */
char	*process_heredoc_token(t_token *token, int *expand_vars,
		t_env_list *env_list)
{
	char	*delimiter;
	char	*cleaned_delimiter;

	delimiter = get_heredoc_delimiter(token, env_list);
	if (!delimiter)
		return (NULL);
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
