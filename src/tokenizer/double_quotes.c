/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 11:12:03 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/15 11:12:51 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Verarbeitet den Inhalt innerhalb der doppelten Anführungszeichen
static void	process_double_quote_content(char *input, int *i,
	t_token_list *token_list)
{
int	start;

start = *i;
while (input[*i] && input[*i] != '"')
{
	if (input[*i] == '$')
	{
		save_text_before_var(input, start, *i, token_list);
		handle_env_var(input, i, token_list);
		start = *i;
	}
	else
		(*i)++;
}
if (!input[*i])
	error_handler("UNCLOSED DOUBLE QUOTE", 1);
save_remaining_text(input, start, *i, token_list);
return ;
}

// Hauptfunktion für doppelte Anführungszeichen
int	handle_double_quote(char *input, int *i, t_token_list *token_list)
{
if (input[*i] != '"')
	return (0);
(*i)++;
process_double_quote_content(input, i, token_list);
(*i)++;
return (1);
}
