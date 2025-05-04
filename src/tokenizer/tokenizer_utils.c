/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 12:26:41 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 12:41:03 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// creates Linked List for tokens
t_token_list *create_token_list(void)
{
	t_token_list *new_list;
	
	new_list = (t_token_list *)gc_malloc(sizeof(t_token_list));
	if(!new_list)
		error_handler("MEMORY ALLOCATION FAILED: CREATE_TOKEN_LIST", 1);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return(new_list);
}
//creates token nodes
t_token *create_token(t_token_type type)