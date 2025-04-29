/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 16:51:29 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/13 21:29:38 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	length(int n)
{
	int	l;

	l = 1;
	if (n < 0)
	{
		n = -n;
		l++;
	}
	while (n > 9)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

static void	convert(char *ptr, int n, int l)
{
	while (l > 0)
	{
		ptr[--l] = (n % 10) + '0';
		n = n / 10;
	}
}

char	*ft_itoa(int n)
{
	char	*ptr;
	int		l;
	int		negativ;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	negativ = (n < 0);
	l = length(n);
	ptr = malloc(l + 1);
	if (ptr == NULL)
		return (NULL);
	if (n == 0)
	{
		ptr[0] = '0';
		ptr[1] = '\0';
		return (ptr);
	}
	ptr[l] = '\0';
	if (negativ)
		n = -n;
	convert(ptr, n, l);
	if (negativ)
		ptr[0] = '-';
	return (ptr);
}
