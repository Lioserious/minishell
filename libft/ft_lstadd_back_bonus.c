#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*content;

	content = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (content -> next != NULL)
		content = content -> next;
	content -> next = new;
}
