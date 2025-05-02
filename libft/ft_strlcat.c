/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:17:03 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:17:03 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
* @brief Verkettung von Strings mit Begrenzung der Puffergröße
*
* Diese Funktion hängt den String 'src' an das Ende des Strings 'dst' an, 
* wobei sichergestellt wird, dass die Gesamtlänge des resultierenden Strings
* kleiner als 'size' ist. Im Gegensatz zu strcat() ist diese Funktion
* größensicher.
* Sie garantiert, dass der resultierende String null-terminiert ist, solange 
* 'size' größer als 0 ist und 'dst' bereits einen null-terminierten
* String enthält.
*
* @param dst Der Zielstring, an den angehängt werden soll
* @param src Der Quellstring, der angehängt werden soll
* @param size Die Größe des Zielpuffers
* @return Die Gesamtlänge des Strings, den die Funktion zu erstellen versucht hat
*         (also die Länge von 'dst' + die Länge von 'src'). Wenn 'size' kleiner
*         als die Länge von 'dst' ist, wird 'size' + Länge von 'src'
*         zurückgegeben.
*/
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_length;
	size_t	i;

	dest_length = ft_strlen(dst);
	i = 0;
	if (dest_length >= size)
		return (ft_strlen(src) + size);
	while (size - 1 > dest_length + i && src[i] != '\0')
	{
		dst[dest_length + i] = src[i];
		i++;
	}
	dst[dest_length + i] = '\0';
	return (dest_length + ft_strlen(src));
}
