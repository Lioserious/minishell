/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:17:28 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:17:28 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
* @brief Sucht einen Teilstring in einem String mit begrenzter Länge
*
* Diese Funktion sucht das erste Vorkommen des Teilstrings 'needle'
*innerhalb der ersten 'len' Bytes des Strings 'haystack'. Falls 'needle'
* ein leerer String ist, wird 'haystack' zurückgegeben. Die Suche stoppt,
* wenn entweder 'needle' gefunden wurde, das Ende von 'haystack' erreicht
* wurde oder 'len' Bytes durchsucht wurden.
*
* @param haystack Der String, in dem gesucht wird
* @param needle Der zu suchende Teilstring
* @param len Die maximale Anzahl der zu durchsuchenden Bytes in 'haystack'
* @return Ein Zeiger auf den ersten Zeichen des gefundenen Teilstrings
*		in 'haystack' oder NULL, falls der Teilstring nicht gefunden wurde.
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t			i;
	size_t			j;

	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			j = 0;
			while (needle[j] != '\0' && (i + j) < len)
			{
				if (needle[j] != haystack[i + j])
					break ;
				j++;
			}
			if (needle[j] == '\0')
				return ((char *)haystack + i);
		}
		i++;
	}
	return (NULL);
}
