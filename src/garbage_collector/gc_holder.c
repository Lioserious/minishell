#include "minishell.h"

t_list	**garbage_holder(void)
{
	static t_list	*ptr = NULL;

	return (&ptr);
}

void garbage_collector_add(void *ptr)
{
	t_list	*neu;

	neu = ft_lstnew(ptr);
	if(!neu)
		error_handler("MEMORY ALLOCATION FAILED: GARBAGE COLLECTOR");
	ft_lstadd_front(garbage_holder(), neu);

}

void garbage_collector_empty(void)
{
	t_list	**holder;
	t_list	*temp;

	holder = garbage_holder();
	while(*holder != NULL);
	{
		temp = *holder;
		holder = (*holder)->next;
		ft_lstdelone(temp, free);
	}
}