/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer__utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:08:01 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 15:21:07 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prüft ob Zeichen Whitespace ist
int	is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

// Prüft ob Zeichen ein Special Character ist
int	is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"' || c == '$');
}

// Prüft ob ein Quote-Zeichen vorliegt
int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
// checkt nach $
int	is_env_var(char c)
{
	return (c == '$');
}
// Extrahiert ein normales Wort
char	*extract_word(char *input, int *i)
{
	int	start;
	int	len;

	start = *i;
	while (input[*i] && !is_whitespace(input[*i])
		&& !is_special_char(input[*i]))
		(*i)++;
	len = *i - start;
	return (gc_substr(input, start, len));
}
