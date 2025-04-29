/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 10:16:07 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/27 18:28:54 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	fake_length(long n);
static void	fake_convert(char *ptr, int n, int l);
static char	*fake_itoa(int n);

int	ft_print_digit(int num)
{
	char	*s_num;
	int		len;

	s_num = fake_itoa(num);
	if (s_num == NULL)
		return (-1);
	len = ft_printstring(s_num);
	free(s_num);
	if (len == -1)
		return (-1);
	return (len);
}

static int	fake_length(long n)
{
	int		l;
	long	num;

	l = 1;
	num = n;
	if (n < 0)
	{
		num = -num;
		l++;
	}
	while (num > 9)
	{
		num = num / 10;
		l++;
	}
	return (l);
}

static void	fake_convert(char *ptr, int n, int l)
{
	long	num;

	num = n;
	if (n < 0)
		num = -num;
	while (l > 0)
	{
		if (l > 1 || n >= 0)
			ptr[--l] = (num % 10) + '0';
		else
			l--;
		num = num / 10;
	}
}

static char	*fake_itoa(int n)
{
	char	*ptr;
	int		l;
	long	num;

	num = n;
	l = fake_length(n);
	ptr = malloc(l + 1);
	if (ptr == NULL)
		return (NULL);
	ptr[l] = '\0';
	if (n < 0)
		ptr[0] = '-';
	if (n == 0)
	{
		ptr[0] = '0';
		return (ptr);
	}
	fake_convert(ptr, num, l);
	return (ptr);
}
