/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:16:07 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:16:07 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Verschiebt einen Speicherbereich in einen anderen
 *
 * Diese Funktion kopiert 'n' Bytes vom Quellspeicherbereich 'src' zum
 * Zielspeicherbereich 'dest'. Im Gegensatz zu ft_memcpy können sich die
 * Speicherbereiche überlappen, ohne dass es zu Korruptionen kommt. Die Funktion
 * erkennt die relative Position der Speicherbereiche und wählt eine geeignete
 * Kopiermethode (vorwärts oder rückwärts),
	um korrekte Ergebnisse zu garantieren.
 * Falls Quelle und Ziel identisch sind oder 'n' gleich 0 ist,
	kehrt die Funktion
 * sofort zurück.
 *
 * @param dest Zeiger auf den Zielspeicherbereich
 * @param src Zeiger auf den Quellspeicherbereich
 * @param n Die Anzahl der zu kopierenden Bytes
 * @return Zeiger auf den Zielspeicherbereich (dest)
 */
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*s;
	unsigned char	*d;

	s = (unsigned char *)src;
	d = (unsigned char *)dest;
	if (d == s || n == 0)
		return (dest);
	if (d < s)
	{
		while (n--)
		{
			*d++ = *s++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			d[i - 1] = s[i - 1];
			i--;
		}
	}
	return (dest);
}
