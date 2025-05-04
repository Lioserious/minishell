/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:26:15 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 16:37:01 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
* tokenizer - Zerlegt Eingabestring in Token-Liste
* @input: Zu zerlegender String (z.B. "echo 'hello' | cat")
*
* Verarbeitet den String Zeichen für Zeichen:
* - Überspringt Whitespace
* - Behandelt Quotes (' und ") 
* - Erkennt ENV Variablen ($ENV)
* - Identifiziert Sonderzeichen (|, <, >, <<, >>)
* - Erfasst normale Wörter/Befehle
*
* Return: Verkettete Liste von Tokens oder NULL bei Fehler
*/
t_token_list	*tokenizer(char *input)
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
		else if (handle_single_quote(input, &i, token_list))
			continue;
		else if (handle_double_quote(input, &i, token_list))
			continue;
		else if (handle_env_var(input, &i, token_list))
			continue;
		else if (handle_special_char(input, &i, token_list))
			continue;
		else if (handle_word(input, &i, token_list))
			continue;
		else
			i++;
	}
	return (token_list);
}
