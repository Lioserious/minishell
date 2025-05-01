#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*n_node;

	n_node = malloc(sizeof(t_list));
	if (n_node == NULL)
		return (NULL);
	n_node -> content = content;
	n_node -> next = NULL;
	return (n_node);
}
