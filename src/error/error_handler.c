#include "minishell.h"

void	error_handler(char *message, int status)
{
	ft_putstr_fd("Error: ", 2);
	ft_putendl_fd(message, 2);
	exit(status);
}
