/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 15:48:11 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/15 11:12:45 by lihrig           ###   ########.fr       */
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

// Speichert Text vor einer Umgebungsvariable
static void	save_text_before_var(char *input, int start, int end,
		t_token_list *token_list)
{
	int		len;
	char	*value;
	t_token	*new_token;

	if (end > start)
	{
		len = end - start;
		value = gc_substr(input, start, len);
		new_token = create_token(TOKEN_WORD, value);
		add_token_to_list(token_list, new_token);
	}
}

// Speichert verbleibenden Text nach der letzten Variable
static void	save_remaining_text(char *input, int start, int end,
		t_token_list *token_list)
{
	int		len;
	char	*value;
	t_token	*new_token;

	if (end > start)
	{
		len = end - start;
		value = gc_substr(input, start, len);
		new_token = create_token(TOKEN_WORD, value);
		add_token_to_list(token_list, new_token);
	}
}
