/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:48:11 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 16:05:10 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_single_quote(char *input, int *i, t_token_list *token_list)
{
	t_token	*new_token;
	int		start;
	int		len;
	char	*value;

	if (input[*i] != '\'')
		return (0);
	start = ++(*i);
	while (input[*i] && input[*i] != '\'')
		(*i)++;
	if (!input[*i])
		error_handler("Unclosed single quote", 1);
	len = *i - start;
	value = gc_substr(input, start, len);
	new_token = create_token(TOKEN_WORD, value);
	add_token_to_list(token_list, new_token);
	(*i)++;
	return (1);
}

int	handle_double_quote(char *input, int *i, t_token_list *token_list)
{
	t_token *new_token;
	int start;
	int len;
	char *value;

	if (input[*i] != '"')
		return (0);
	(*i)++;
	start = *i;
	while (input[*i] && input[*i] != '"')
}