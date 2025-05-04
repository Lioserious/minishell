/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:52:00 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 13:55:53 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// TOKEN_WORD,              // Normale Wörter
// 	TOKEN_PIPE,          // |
// 	TOKEN_REDIR_IN,      //
// 	TOKEN_REDIR_OUT,     // >
// 	TOKEN_REDIR_APPEND,  // >>
// 	TOKEN_REDIR_HEREDOC, //
// 	TOKEN_EOF            // Ende des Inputs

int handle_special_char(char *input, int *i, t_token_list *token_list)
{
	t_token	*new_token;

	if (input[*i] == '|')
	{
		new_token = create_token(TOKEN_PIPE, "|");
		add_token_to_list(token_list, new_token);
		(*i)++;
		return (1);
	}
	else if (input[*i] == '<')
	{
		if (input[*i + 1] == '<')
		{
			new_token = create_token(TOKEN_REDIR_HEREDOC, "<<");
			(*i) += 2;
		}
		else
		{
			new_token = create_token(TOKEN_REDIR_IN, "<");
			(*i)++;
		}
		add_token_to_list(token_list, new_token);
		return (1);
	}
	else if (input[*i] == '>')
    {
        if (input[*i + 1] == '>')
        {
            new_token = create_token(TOKEN_REDIR_APPEND, ">>");
            (*i) += 2;
        }
        else
        {
            new_token = create_token(TOKEN_REDIR_OUT, ">");
            (*i)++;
        }
        add_token_to_list(token_list, new_token);
        return (1);
    }
    else if (input[*i] == '\'' || input[*i] == '"')
		return(0);
    return (0); 
}
