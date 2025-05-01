#include "ft_printf.h"

int	to_hex_upp(unsigned long n)
{
	char	*hex;
	int		count;
	int		write_output;

	hex = "0123456789ABCDEF";
	count = 0;
	if (n >= 16)
	{
		count = to_hex_upp(n / 16);
		if (count == -1)
			return (-1);
	}
	write_output = write(1, &hex[n % 16], 1);
	if (write_output == -1)
		return (-1);
	return (count + 1);
}

int	to_hex_low(unsigned long n)
{
	char	*hex;
	int		count;
	int		write_output;

	hex = "0123456789abcdef";
	count = 0;
	if (n >= 16)
	{
		count = to_hex_low(n / 16);
		if (count == -1)
			return (-1);
	}
	write_output = write(1, &hex[n % 16], 1);
	if (write_output == -1)
		return (-1);
	return (count + 1);
}
