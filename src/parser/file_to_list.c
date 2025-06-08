/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_list.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:31:08 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/22 18:50:46 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// initialisiert file list als container fuer die redirections
t_file_list	*create_file_list(void)
{
	t_file_list	*new_list;

	new_list = (t_file_list *)gc_malloc(sizeof(t_file_list));
	if (!new_list)
		return (error_handler("MEMORY ALLOCATION FAILED: CREATE_FILE_LIST", 0));
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return (new_list);
}

// creates file node needs "add_cmd_to_list" to connect with list
t_file_node	*create_file_node(char *name, int redirection_type)
{
	t_file_node	*new_node;

	new_node = (t_file_node *)gc_malloc(sizeof(t_file_node));
	if (!new_node)
		return (error_handler("MEMORY ALLOCATION FAILED: CREATE_FILE_NODE", 0));
	new_node->name = name;
	new_node->redirection_type = redirection_type;
	new_node->heredoc_fd = -1;
	new_node->expand_vars = 1;
	new_node->next = NULL;
	return (new_node);
}

void	add_files_list(t_file_list *list, t_file_node *node)
{
	if (!list || !node)
		return ;
	if (list->size == 0)
	{
		list->head = node;
		list->tail = node;
	}
	else
	{
		list->tail->next = node;
		list->tail = node;
	}
	list->size++;
}
