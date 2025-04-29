/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_unsigned_digit.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:40:15 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/27 18:27:36 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	fake_length_unsigned(unsigned int n);
static void	fake_convert_unsigned(char *ptr, unsigned int n, int l);
static char	*fake_itoa_unsigned(unsigned int n);

int	ft_print_digit_unsigned(unsigned int num)
{
	char	*s_num;
	int		len;

	s_num = fake_itoa_unsigned(num);
	if (s_num == NULL)
		return (-1);
	len = ft_printstring(s_num);
	free(s_num);
	if (len == -1)
		return (-1);
	return (len);
}

static int	fake_length_unsigned(unsigned int n)
{
	int		l;

	l = 1;
	while (n > 9)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

static void	fake_convert_unsigned(char *ptr, unsigned int n, int l)
{
	while (l > 0)
	{
		ptr[--l] = (n % 10) + '0';
		n = n / 10;
	}
}

static char	*fake_itoa_unsigned(unsigned int n)
{
	char	*ptr;
	int		l;

	l = fake_length_unsigned(n);
	ptr = malloc(l + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[l] = '\0';
	fake_convert_unsigned(ptr, n, l);
	return (ptr);
}
