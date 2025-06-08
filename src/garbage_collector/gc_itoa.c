/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 14:30:27 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/30 14:31:08 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/**
 * @brief Konvertiert einen Integer in einen String
 *
 * Diese Funktion konvertiert einen Integer-Wert in einen neu allozierten
 * String. Sie behandelt positive und negative Zahlen, inklusive Sonderfälle

	* wie INT_MIN und 0. Der zurückgegebene String muss vom Aufrufer freigegeben
	* werden.
 *
 * @param n Der zu konvertierende Integer-Wert
 * @return Ein neu allozierter String mit der Zahl oder NULL bei Fehlern
 */
char	*gc_itoa(int n)
{
	char	*ptr;
	int		l;
	int		negativ;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	negativ = (n < 0);
	l = length(n);
	ptr = gc_malloc(l + 1);
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
