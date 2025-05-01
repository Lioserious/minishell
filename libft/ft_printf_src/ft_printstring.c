#include "ft_printf.h"

int	ft_printstring(const char *s)
{
	int			i;
	const char	*null_s;

	null_s = "(null)";
	i = 0;
	if (s == NULL)
		return (ft_printstring(null_s));
	if (s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (ft_printchar(s[i]) == -1)
			return (-1);
		i++;
	}
	return (i);
}
