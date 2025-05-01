#include "ft_printf.h"

int	ft_print_digit_hex_upp(unsigned int n)
{
	int	output;

	output = to_hex_upp(n);
	if (output == -1)
		return (-1);
	else
		return (output);
}

int	ft_print_digit_hex_low(unsigned int n)
{
	int	output;

	output = to_hex_low(n);
	if (output == -1)
		return (-1);
	else
		return (output);
}
