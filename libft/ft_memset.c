/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:16:13 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:16:13 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Füllt einen Speicherbereich mit einem bestimmten Wert
 *
 * Diese Funktion setzt die ersten 'len' Bytes des Speicherbereichs, auf den
 * 'b' zeigt, auf den Wert 'c'. Der Wert wird als unsigned char interpretiert.

	* Die Funktion ist nützlich zum Initialisieren oder Zurücksetzen
	* von Speicherbereichen
 * auf einen bestimmten Wert.
 *
 * @param b Zeiger auf den zu füllenden Speicherbereich
 * @param c Der Wert,
	mit dem gefüllt werden soll (wird als unsigned char interpretiert)
 * @param len Die Anzahl der zu füllenden Bytes
 * @return Zeiger auf den Speicherbereich (b)
 */
void	*ft_memset(void *b, int c, size_t len)
{
	size_t			i;
	unsigned char	*p;

	p = (unsigned char *)b;
	i = 0;
	while (i < len)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (b);
}
