#include "ft_printf.h"

int	ft_print_void(void *ptr)
{
	int	printed;
	int	output;

	printed = 2;
	if (ptr == NULL)
	{
		output = ft_printstring("0x0");
		if (output == -1)
			return (-1);
		return (3);
	}
	output = ft_printstring("0x");
	if (output == -1)
		return (-1);
	output = to_hex_low((unsigned long)ptr);
	if (output == -1)
		return (-1);
	return (printed + output);
}
