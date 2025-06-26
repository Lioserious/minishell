/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:31:01 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/26 17:12:33 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Ein Perlenfaden, der bereit ist viele Perlen aufzunehmen
// inklusiv gc_malloc
t_cmd_list	*create_cmd_list(void)
{
	t_cmd_list	*new_list;

	new_list = (t_cmd_list *)gc_malloc(sizeof(t_cmd_list));
	if (!new_list)
		return (error_handler("MEMORY ALLOCATION FAILED: CREATE_CMD_LIST", 0));
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return (new_list);
}

// cmd_types defined in cmd_types.h -> Perlen
t_cmd_node	*create_cmd_node(char **cmd, int cmd_type)
{
	t_cmd_node	*new_node;

	new_node = (t_cmd_node *)gc_malloc(sizeof(t_cmd_node));
	if (!new_node)
		return (error_handler("MEMORY ALLOCATION FAILED: CREATE_CMD_NODE", 0));
	if (!cmd)
	{
		new_node->cmd = (char **)gc_malloc(sizeof(char *) * 1);
		new_node->cmd[0] = NULL;
	}
	else
	{
		new_node->cmd = cmd;
	}
	new_node->cmd_type = cmd_type;
	new_node->file = create_file_list();
	new_node->next = NULL;
	return (new_node);
}

// auffedel funktion verbindet liste mit neuem node,
void	add_cmd_to_list(t_cmd_list *list, t_cmd_node *node)
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
