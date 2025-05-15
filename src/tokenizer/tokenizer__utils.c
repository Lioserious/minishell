/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer__utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:08:01 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/15 21:20:56 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if character is a special operator
 * @param c Character to check
 * @return 1 if character is pipe or redirection, 0 otherwise
 */
int	is_special_operator(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/**
 * @brief Appends a part to a word string
 * @param word Pointer to word string
 * @param part String to append
 */
void	add_to_word(char **word, char *part)
{
	char	*temp;

	if (*word == NULL)
	{
		*word = gc_strdup(part);
	}
	else
	{
		temp = gc_strjoin(*word, part);
		*word = temp;
	}
}

/**
 * @brief Checks if character is whitespace
 * @param c Character to check
 * @return 1 if character is space, tab or newline, 0 otherwise
 */
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

/**
 * @brief Checks if character is a quote
 * @param c Character to check
 * @return 1 if character is single or double quote, 0 otherwise
 */
int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

/**
 * @brief Checks if character marks start of environment variable
 * @param c Character to check
 * @return 1 if character is dollar sign, 0 otherwise
 */
int	is_env_var(char c)
{
	return (c == '$');
}
