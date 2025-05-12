/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:31:01 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/12 12:33:12 by lihrig           ###   ########.fr       */
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
		error_handler("MEMORY ALLOCATION FAILED: CREATE_CMD_LIST", 1);
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
		error_handler("MEMORY ALLOCATION FAILED: CREATE_CMD_NODE", 1);
	new_node->cmd = cmd;
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
// MUSS NOCH RAUS
void	print_parsed_cmd_list(t_cmd_list *cmd_list)
{
    t_cmd_node	*current;
    int			i;

    if (!cmd_list)
    {
        printf("Empty command list\n");
        return;
    }
    printf("Command list with %zd command(s):\n", cmd_list->size);
        current = cmd_list->head;
    while (current)
    {
        printf("Command Type: %d\n", current->cmd_type);
        if (current->cmd)
        {
            i = 0;
            printf("  Args: ");
            while (current->cmd[i])
            {
                printf("[%s] ", current->cmd[i]);
                i++;
            }
            printf("\n");
        }
        current = current->next;
        printf("-----------------\n");
    }
}
