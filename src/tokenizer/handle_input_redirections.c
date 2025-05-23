/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_input_redirections.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 15:24:03 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/23 16:25:12 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Sammelt einen gequoteten Heredoc-Delimiter
 * @param input Input-String
 * @param i Aktuelle Position (wird aktualisiert)
 * @param quote_char Das Quote-Zeichen (' oder ")
 * @return Der Delimiter MIT Quotes
 */
char	*collect_quoted_delimiter(char *input, int *i, char quote_char)
{
	int		start;
	char	*delimiter;

	start = *i - 1;
	while (input[*i] && input[*i] != quote_char)
		(*i)++;
	if (input[*i] == quote_char)
		(*i)++;
	else
		return (error_handler("Unclosed quote in heredoc delimiter", 0));
	delimiter = gc_substr(input, start, *i - start);
	return (delimiter);
}

/**
 * @brief Sammelt einen ungequoteten Heredoc-Delimiter
 * @param input Input-String
 * @param i Aktuelle Position (wird aktualisiert)
 * @return Der Delimiter ohne Quotes
 */
char	*collect_unquoted_delimiter(char *input, int *i)
{
	int		start;
	char	*delimiter;

	start = *i;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_operator(input[*i]))
		(*i)++;
	delimiter = gc_substr(input, start, *i - start);
	return (delimiter);
}

/**
 * @brief Verarbeitet den Heredoc-Delimiter nach <<
 * @param input Input-String
 * @param i Aktuelle Position (wird aktualisiert)
 * @param token_list Token-Liste zum Hinzufügen
 */
void	handle_heredoc_delimiter(char *input, int *i, t_token_list *token_list)
{
	char	*delimiter;
	t_token	*delim_token;
	char	quote;

	while (input[*i] && is_whitespace(input[*i]))
		(*i)++;
	if (input[*i] == '"' || input[*i] == '\'')
	{
		quote = input[*i];
		(*i)++;
		delimiter = collect_quoted_delimiter(input, i, quote);
	}
	else
	{
		delimiter = collect_unquoted_delimiter(input, i);
	}
	if (delimiter)
	{
		delim_token = create_token(TOKEN_WORD, delimiter);
		add_token_to_list(token_list, delim_token);
	}
}

/**
 * @brief Behandelt Heredoc (<<)
 * @param input Input-String
 * @param i Aktuelle Position (wird aktualisiert)
 * @param token_list Token-Liste zum Hinzufügen
 */
void	handle_heredoc(char *input, int *i, t_token_list *token_list)
{
	t_token	*heredoc_token;

	heredoc_token = create_token(TOKEN_REDIR_HEREDOC, "<<");
	add_token_to_list(token_list, heredoc_token);
	(*i) += 2;
	handle_heredoc_delimiter(input, i, token_list);
}

/**
 * @brief Behandelt normale Input-Redirection (<)
 * @param input Input-String
 * @param i Aktuelle Position (wird aktualisiert)
 * @param token_list Token-Liste zum Hinzufügen
 */
void	handle_simple_input_redir(char *input, int *i, t_token_list *token_list)
{
	t_token	*redir_token;

	(void)input;
	redir_token = create_token(TOKEN_REDIR_IN, "<");
	add_token_to_list(token_list, redir_token);
	(*i)++;
}
