/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_token.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 13:49:46 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/02 13:51:20 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if token sequence starts with a pipe
 * @param token_list Token list to check
 * @return 1 if valid start, 0 if invalid
 */
static int	validate_start_token(t_token_list *token_list)
{
	if (!token_list || !token_list->head)
		return (1);
	if (token_list->head->type == TOKEN_PIPE)
	{
		error_handler("syntax error near unexpected token '|'", 0);
		return (0);
	}
	return (1);
}

/**
 * @brief Checks if token sequence ends with a pipe
 * @param token_list Token list to check
 * @return 1 if valid end, 0 if invalid
 */
static int	validate_end_token(t_token_list *token_list)
{
	if (!token_list || !token_list->tail)
		return (1);
	if (token_list->tail->type == TOKEN_PIPE)
	{
		error_handler("syntax error near unexpected token '|'", 0);
		return (0);
	}
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
	if (current->type == TOKEN_PIPE && next->type == TOKEN_PIPE)
	{
		error_handler("syntax error near unexpected token '|'", 0);
		return (0);
	}
	if (is_redirection_token(current->type) && next->type == TOKEN_PIPE)
	{
		error_handler("syntax error near unexpected token '|'", 0);
		return (0);
	}
	return (1);
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
	while (current && current->next)
	{
		next = current->next;
		if (!validate_token_pair(current, next))
			return (0);
		current = next;
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
