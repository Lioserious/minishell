#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	if (s)
	{
		while (s[counter])
			counter++;
	}
	return (counter);
}
