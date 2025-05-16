/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:48:59 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/16 18:02:59 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Processes normal characters up to a special character
 * @param input Input string
 * @param i Current position pointer
 * @return Extracted text segment
 */
char	*process_word_part(char *input, int *i)
{
	int		start;
	char	*word_part;

	start = *i;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_operator(input[*i]) && input[*i] != '\''
		&& input[*i] != '"' && input[*i] != '$')
	{
		(*i)++;
	}
	word_part = gc_substr(input, start, *i - start);
	return (word_part);
}

/**
 * @brief Processes different quote and variable types in a word
 * @param input Input string
 * @param i Current position pointer
 * @param current_word Pointer to current word being built
 * @param env_list Environment variable list
 * @return 1 if a part was processed, 0 otherwise
 */
static int	process_special_part(char *input, int *i, char **current_word,
		t_env_list *env_list)
{
	char	*part;
	part = NULL;
	if (input[*i] == '~')
	{
		part = process_tilde(input, i, env_list);
		if (part != NULL)
		{
			add_to_word(current_word, part);
			return (1);
		}
	}
	if (input[*i] == '\'')
		part = process_single_quote(input, i);
	else if (input[*i] == '"')
		part = process_double_quote(input, i, env_list);
	else if (input[*i] == '$')
		part = process_env_var(input, i, env_list);
	else
		part = process_word_part(input, i);
	if (part != NULL)
		return (add_to_word(current_word, part), 1);
	return (0);
}

/**
 * @brief Verarbeitet ein Wort und aktualisiert die Token-Liste
 * @param input Input string
 * @param i Current position pointer
 * @param token_list Token list to update
 * @param env_list Environment variable list
 */
void	process_word(char *input, int *i, t_token_list *token_list,
		t_env_list *env_list)
{
	char	*current_word;

	current_word = NULL;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_operator(input[*i]))
	{
		process_special_part(input, i, &current_word, env_list);
	}
	if (current_word != NULL)
	{
		add_word_token(token_list, current_word);
	}
}
