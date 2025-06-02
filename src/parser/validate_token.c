/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:49:46 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/02 14:51:41 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if token sequence ends with a pipe
 * @param token_list Token list to check
 * @return 1 if valid end, 0 if invalid
 */
static int	validate_end_token(t_token_list *token_list)
{
	t_token	*current;

	if (!token_list || !token_list->head)
		return (1);
	current = token_list->head;
	while (current && current->next && current->next->type != TOKEN_EOF)
		current = current->next;
	if (current && current->type == TOKEN_PIPE)
		return (pipe_syntax_error());
	return (1);
}

/**
 * @brief Checks for invalid token pair combinations
 * @param current Current token
 * @param next Next token
 * @return 1 if valid pair, 0 if invalid
 */
static int	validate_token_pair(t_token *current, t_token *next)
{
	if (is_empty_token(current) || is_empty_token(next))
		return (1);
	if (current->type == TOKEN_PIPE && next->type == TOKEN_PIPE)
		return (pipe_syntax_error());
	if (is_redirection_token(current->type) && next->type == TOKEN_PIPE)
		return (pipe_syntax_error());
	return (1);
}

/**
 * @brief Gets next non-empty token
 * @param token Starting token
 * @return Next non-empty token or NULL
 */
static t_token	*get_next_valid_token(t_token *token)
{
	t_token	*next;

	if (!token)
		return (NULL);
	next = token->next;
	while (next && is_empty_token(next))
		next = next->next;
	return (next);
}

/**
 * @brief Validates all token pairs in sequence
 * @param token_list Token list to validate
 * @return 1 if valid sequence, 0 if invalid
 */
static int	validate_token_pairs(t_token_list *token_list)
{
	t_token	*current;
	t_token	*next;

	if (!token_list || !token_list->head)
		return (1);
	current = token_list->head;
	while (current)
	{
		next = get_next_valid_token(current);
		if (!next)
			break ;
		if (!validate_token_pair(current, next))
			return (0);
		current = current->next;
	}
	return (1);
}

/**
 * @brief Main validation function - validates entire token sequence
 * @param token_list Token list to validate
 * @return 1 if valid, 0 if invalid
 */
int	validate_token_sequence(t_token_list *token_list)
{
	if (!validate_start_token(token_list))
		return (0);
	if (!validate_token_pairs(token_list))
		return (0);
	if (!validate_end_token(token_list))
		return (0);
	return (1);
}
