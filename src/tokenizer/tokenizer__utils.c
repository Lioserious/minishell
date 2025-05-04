/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer__utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:08:01 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 13:30:04 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Prüft ob Zeichen Whitespace ist
int is_whitespace(char c)
{
    return (c == ' ' || c == '\t' || c == '\n');
}

// Prüft ob Zeichen ein Special Character ist
int is_special_char(char c)
{
    return (c == '|' || c == '<' || c == '>' || c == '\'' || c == '"');
}

void handle_special_char(char *input, int *i, t_token_list *token_list)
{
	
}

// Extrahiert ein normales Wort
char *extract_word(char *input, int *i)
{
    int start;
    int len;
    
    start = *i;
    while (input[*i] && !is_whitespace(input[*i]) && !is_special_char(input[*i]))
        (*i)++;
    
    len = *i - start;
    return (gc_substr(input, start, len));
}
