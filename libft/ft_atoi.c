#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		num;
	int		minus;

	i = 0;
	minus = 1;
	num = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		minus = -1;
	if (minus == -1 || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (num > (2147483647 - (str[i] - '0')) / 10)
		{
			if (minus == -1)
				return (-2147483648);
			return (2147483647);
		}
		num = (num * 10) + (str[i] - '0');
		i++;
	}
	return (num * minus);
}
