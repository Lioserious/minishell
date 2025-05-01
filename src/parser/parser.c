#include "minishell.h"

t_cmd_list *create_cmd_list(void)
{
	t_cmd_list *new_list;

	new_list = (t_cmd_list *)gc_malloc(sizeof(t_cmd_list));
	if(!new_list)
		error_handler("MEMORY ALLOCATION FAILED: CREATE_CMD_LIST", 1);
	new_list->head = NULL;
	new_list->tail = NULL;
	new_list->size = 0;
	return(new_list);
}