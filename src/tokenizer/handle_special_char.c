/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_special_char.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:52:00 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/23 15:27:26 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TOKEN_WORD,           // Commands, arguments, filenames
// TOKEN_PIPE,           // |
// TOKEN_REDIR_IN,       //
// TOKEN_REDIR_OUT,      // >
// TOKEN_REDIR_APPEND,   // >>
// TOKEN_REDIR_HEREDOC,  //
// TOKEN_ENV_VAR,        // $VAR, $?
// TOKEN_EOF            // End of input

// Behandelt Pipe |
int	handle_pipe(char *input, int *i, t_token_list *token_list)
{
	t_token	*new_token;

	if (input[*i] == '|')
	{
		new_token = create_token(TOKEN_PIPE, "|");
		add_token_to_list(token_list, new_token);
		(*i)++;
		return (1);
	}
	return (0);
}

// Behandelt Input Redirection < und
// int	handle_input_redirection(char *input, int *i, t_token_list *token_list)
// {
// 	t_token	*new_token;

// 	if (input[*i] == '<')
// 	{
// 		if (input[*i + 1] == '<')
// 		{
// 			new_token = create_token(TOKEN_REDIR_HEREDOC, "<<");
// 			add_token_to_list(token_list, new_token);
// 			(*i) += 2;
// 		}
// 		else
// 		{
// 			new_token = create_token(TOKEN_REDIR_IN, "<");
// 			add_token_to_list(token_list, new_token);
// 			(*i)++;
// 		}
// 		return (1);
// 	}
// 	return (0);
// }

// Behandelt Output Redirection > und >>
int	handle_output_redirection(char *input, int *i, t_token_list *token_list)
{
	t_token	*new_token;

	if (input[*i] == '>')
	{
		if (input[*i + 1] == '>')
		{
			new_token = create_token(TOKEN_REDIR_APPEND, ">>");
			add_token_to_list(token_list, new_token);
			(*i) += 2;
		}
		else
		{
			new_token = create_token(TOKEN_REDIR_OUT, ">");
			add_token_to_list(token_list, new_token);
			(*i)++;
		}
		return (1);
	}
	return (0);
}

// Hauptfunktion für Special Characters
int	handle_special_char(char *input, int *i, t_token_list *token_list)
{
	if (handle_pipe(input, i, token_list))
		return (1);
	if (handle_input_redirection(input, i, token_list))
		return (1);
	if (handle_output_redirection(input, i, token_list))
		return (1);
	if (is_env_var(input[*i]))
		return (0);
	if (is_quote(input[*i]))
		return (0);
	return (0);
}
