/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_token_helper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:45:48 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/03 20:28:25 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if token is empty or invalid
 * @param token Token to check
 * @return 1 if token should be skipped, 0 otherwise
 */
int	is_empty_token(t_token *token)
{
	return (!token || !token->value || token->value[0] == '\0');
}

/**
 * @brief Prints syntax error for pipe token
 * @return Always returns 0 (invalid)
 */
int	pipe_syntax_error(void)
{
	error_handler("syntax error near unexpected token '|'", 0);
	return (0);
}

/**
 * @brief Checks if token sequence starts with a pipe
 * @param token_list Token list to check
 * @return 1 if valid start, 0 if invalid
 */
int	validate_start_token(t_token_list *token_list)
{
	if (!token_list || !token_list->head)
		return (1);
	if (is_redirection_token(token_list->head->type))
	{
		error_handler("syntax error near unexpected token", 0);
		return (0);
	}
	if (token_list->head->type == TOKEN_PIPE)
		return (pipe_syntax_error());
	return (1);
}
