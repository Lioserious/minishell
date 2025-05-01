#include "minishell.h"

t_list	**garbage_holder(void)
{
	static t_list	*ptr = NULL;

	return (&ptr);
}