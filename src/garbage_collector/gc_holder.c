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
		error_handler("MEMORY ALLOCATION FAILED: GARBAGE COLLECTOR", 2);
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

void	garbage_collector_print(void)
{
	t_list	*temp;
	size_t	i;

	temp = *garbage_holder();
	i = 0;
	while (temp != NULL)
	{
		printf("Pointer %zu: %p, %s\n", i, temp->content, (char *)temp->content);
		temp = temp->next;
		i++;
	}
}
