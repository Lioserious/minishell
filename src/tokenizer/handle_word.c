/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:48:59 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 17:23:29 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_word(char *input, int *i, t_token_list *token_list)
{
	t_token	*new_token;
	char	*word;

	if (!input[*i] || is_whitespace(input[*i]) || is_special_char(input[*i]))
		return (0);
	word = extract_word(input, i);
	if (!word)
		return (0);
	new_token = create_token(TOKEN_WORD, word);
	add_token_to_list(token_list, new_token);
	return (1);
}
