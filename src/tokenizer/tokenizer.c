/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:26:15 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/15 21:21:03 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a word token and adds it to token list
 * @param token_list Token list to update
 * @param word Word string to tokenize
 */
void	add_word_token(t_token_list *token_list, char *word)
{
	t_token	*new_token;

	if (word == NULL)
		return ;
	new_token = create_token(TOKEN_WORD, word);
	add_token_to_list(token_list, new_token);
}

/**
 * @brief Tokenizes input string into a list of tokens
 * @param input String to tokenize
 * @param env_list Environment variable list
 * @return Token list or NULL on error
 *
 * Processes string character by character:
 * - Skips whitespace
 * - Handles quotes and environment variables
 * - Identifies special operators
 * - Captures normal words/commands
 */
t_token_list	*tokenizer(char *input, t_env_list *env_list)
{
	t_token_list	*token_list;
	int				i;

	token_list = create_token_list();
	if (!token_list)
		return (NULL);
	i = 0;
	while (input[i])
	{
		if (is_whitespace(input[i]))
			i++;
		else if (is_special_operator(input[i]))
			handle_special_char(input, &i, token_list);
		else
			process_word(input, &i, token_list, env_list);
	}
	add_eof_token(token_list);
	return (token_list);
}
