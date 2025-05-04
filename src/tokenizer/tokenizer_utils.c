/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:26:41 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 16:25:19 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates Linked List for tokens
t_token_list	*create_token_list(void)
{
	t_token_list	*new_list;

	new_list = (t_token_list *)gc_malloc(sizeof(t_token_list));
	if (!new_list)
		error_handler("MEMORY ALLOCATION FAILED: CREATE_TOKEN_LIST", 1);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return (new_list);
}

// creates token nodes
t_token	*create_token(t_token_type type, char *value)
{
	t_token	*new_token;

	new_token = (t_token *)gc_malloc(sizeof(t_token));
	if (!new_token)
		error_handler("MEMORY ALLOCATION FAILED: CREATE_TOKEN", 1);
	new_token->type = type;
	new_token->value = gc_strdup(value);
	if (!new_token->value)
		error_handler("MEMORY ALLOCATION FAILED: CREATE_TOKEN", 1);
	new_token->next = NULL;
	return (new_token);
}

// adds token to list
void	add_token_to_list(t_token_list *list, t_token *token)
{
	if (!list || !token)
		return ;
	if (list->size == 0)
	{
		list->head = token;
		list->tail = token;
	}
	else
	{
		list->tail->next = token;
		list->tail = token;
	}
	list->size++;
}
