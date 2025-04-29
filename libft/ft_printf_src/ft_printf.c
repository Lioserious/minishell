/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 19:56:11 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/27 18:26:27 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	handle_form(va_list args, char format);
static int	convert_one(va_list args, char format);
static int	convert_two(va_list args, char format);
static int	convert_three(va_list args, char format);

int	ft_printf(const char *form, ...)
{
	int		i;
	va_list	args;
	int		printed;
	int		sum;

	va_start(args, form);
	i = 0;
	printed = 0;
	while (form[i] != '\0')
	{
		if (form[i] == '%')
		{
			i++;
			sum = handle_form(args, form[i]);
		}
		else
			sum = ft_printchar(form[i]);
		if (sum == -1)
			return (va_end(args), -1);
		printed += sum;
		i++;
	}
	return (va_end(args), printed);
}

static int	handle_form(va_list args, char format)
{
	if (format == '%')
		return (ft_printchar('%'));
	if (format == 'c' || format == 's' || format == 'd' || format == 'i')
		return (convert_one(args, format));
	if (format == 'u' || format == 'p')
		return (convert_two(args, format));
	if (format == 'x' || format == 'X')
		return (convert_three(args, format));
	return (0);
}

static int	convert_one(va_list args, char format)
{
	int		printed;

	printed = 0;
	if (format == 'c')
	{
		if (ft_printchar((char)(va_arg(args, int))) == -1)
			return (-1);
		return (1);
	}
	if (format == 's')
	{
		printed += ft_printstring(va_arg(args, const char *));
		if (printed == -1)
			return (-1);
		return (printed);
	}
	if (format == 'd' || format == 'i')
	{
		printed = ft_print_digit(va_arg(args, int));
		if (printed == -1)
			return (-1);
		return (printed);
	}
	return (0);
}

static int	convert_two(va_list args, char format)
{
	int		printed;

	printed = 0;
	if (format == 'u')
	{
		printed = ft_print_digit_unsigned(va_arg(args, int));
		if (printed == -1)
			return (-1);
		return (printed);
	}
	if (format == 'p')
	{
		printed = ft_print_void(va_arg(args, void *));
		if (printed == -1)
			return (-1);
		return (printed);
	}
	return (0);
}

static int	convert_three(va_list args, char format)
{
	int	printed;

	printed = 0;
	if (format == 'x')
	{
		printed = ft_print_digit_hex_low(va_arg(args, unsigned int));
		if (printed == -1)
			return (-1);
		return (printed);
	}
	if (format == 'X')
	{
		printed = ft_print_digit_hex_upp(va_arg(args, unsigned int));
		if (printed == -1)
			return (-1);
		return (printed);
	}
	return (0);
}
