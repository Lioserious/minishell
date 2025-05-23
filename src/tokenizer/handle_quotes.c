/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:48:11 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/23 15:36:04 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Extracts content between single quotes
 * @param input Input string
 * @param i Current position pointer
 * @return Extracted content or NULL
 */
char	*process_single_quote(char *input, int *i)
{
	int		start;
	char	*result;

	if (input[*i] != '\'')
		return (NULL);
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (!input[*i])
		return (error_handler("UNCLOSED SINGLE QUOTE", 0));
	result = gc_substr(input, start, *i - start);
	(*i)++;
	return (result);
}

/**
 * @brief Appends string to result
 * @param result Result string pointer
 * @param str String to append
 */
static void	append_to_result(char **result, char *str)
{
	char	*temp;

	if (*result == NULL)
		*result = str;
	else
	{
		temp = gc_strjoin(*result, str);
		*result = temp;
	}
}

/**
 * @brief Processes text segment with variable in double quotes
 * @param parser Struktur mit allen benötigten Parametern
 */
static void	process_double_quote_part(t_quote_parser *parser)
{
	char	*before;
	char	*var_value;

	if (*parser->i_ptr > *parser->start_ptr)
	{
		before = gc_substr(parser->input, *parser->start_ptr, *parser->i_ptr
				- *parser->start_ptr);
		append_to_result(parser->result, before);
	}
	var_value = process_env_var(parser->input, parser->i_ptr, parser->env_list);
	if (var_value != NULL)
	{
		append_to_result(parser->result, var_value);
	}
	*parser->start_ptr = *parser->i_ptr;
}

/**
 * @brief Processes remaining text after last variable
 * @param input Input string
 * @param i Current position pointer
 * @param start Segment start position
 * @param result Result string pointer
 */
static void	process_remaining_text(char *input, int *i, int start,
		char **result)
{
	char	*after;
	char	*temp;

	if (*i > start)
	{
		after = gc_substr(input, start, *i - start);
		if (*result == NULL)
		{
			*result = after;
		}
		else
		{
			temp = gc_strjoin(*result, after);
			*result = temp;
		}
	}
}

/**
 * @brief Extracts content between double quotes with variable expansion
 * @param input Input string
 * @param i Current position pointer
 * @param env_list Environment variable list
 * @return Processed content or NULL
 */
char	*process_double_quote(char *input, int *i, t_env_list *env_list)
{
	int				start;
	char			*result;
	t_quote_parser	parser;

	result = NULL;
	if (input[*i] != '"')
		return (NULL);
	(*i)++;
	start = *i;
	init_quote_parser_base(&parser, input, i, &result);
	complete_quote_parser(&parser, &start, env_list);
	while (input[*i] && input[*i] != '"')
	{
		if (input[*i] == '$')
			process_double_quote_part(&parser);
		else
			(*i)++;
	}
	process_remaining_text(input, i, start, &result);
	if (!input[*i])
		return (error_handler("UNCLOSED DOUBLE QUOTE", 0));
	(*i)++;
	if (result == NULL)
		result = gc_strdup("");
	return (result);
}
