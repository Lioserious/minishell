/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:47:29 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/15 16:18:33 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	if (n == INT_MIN)
		return (11);
	if (n < 0)
	{
		l++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

static void	convert(char *ptr, int n, int l)
{
	unsigned int	num;

	num = n;
	if (n < 0)
	{
		*ptr = '-';
		num = -num;
	}
	if (num == 0)
		*ptr = '0';
	ptr[l--] = '\0';
	while (num)
	{
		ptr[l--] = (num % 10) + '0';
		num /= 10;
	}
}

static void	fake_ft_itoa(int n, char *ptr)
{
	int	l;

	l = length(n);
	convert(ptr, n, l);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	nbr[12];

	fake_ft_itoa(n, nbr);
	write (fd, nbr, ft_strlen(nbr));
}
