/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:17:08 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:17:08 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
* @brief Kopiert einen String mit Begrenzung der Puffergröße
*
* Diese Funktion kopiert den String 'src' in den Puffer 'dest', wobei
* sichergestellt
* wird, dass die Gesamtlänge des resultierenden Strings kleiner als 'size' ist.
* Im Gegensatz zu strcpy() ist diese Funktion größensicher. Sie garantiert,
* dass der resultierende String null-terminiert ist, solange 'size'
* größer als 0 ist.
*
* @param dest Der Zielpuffer, in den kopiert werden soll
* @param src Der zu kopierende Quellstring
* @param size Die Größe des Zielpuffers
* @return Die Länge des Quellstrings 'src' (ohne Null-Terminator). 
* Dies ermöglicht dem Aufrufer zu erkennen, ob eine Kürzung stattgefunden hat.
*/
size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	length;

	i = 0;
	length = ft_strlen(src);
	if (size == 0)
	{
		return (length);
	}
	while (src[i] != '\0' && i < size - 1)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (length);
}
