/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:17:32 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:17:32 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
* @brief Sucht das letzte Vorkommen eines Zeichens in einem String
*
* Diese Funktion durchsucht den String 's' rückwärts und gibt einen Zeiger
* auf das letzte Vorkommen des Zeichens 'c' zurück. Wenn 'c' als '\0' übergeben
* wird,
* wird ein Zeiger auf den abschließenden Null-Terminator von 's' zurückgegeben.
* Falls das Zeichen nicht gefunden wird, wird NULL zurückgegeben.
*
* @param s Der zu durchsuchende String
* @param c Das zu suchende Zeichen (als int, wird zu unsigned char gecastet)
* @return Ein Zeiger auf das letzte Vorkommen des Zeichens in 's' oder NULL,
* falls nicht gefunden
*/
char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;

	cc = (unsigned char) c;
	i = ft_strlen(s);
	if (cc == '\0')
		return ((char *)(s + i));
	while (i > 0)
	{
		if (s[i - 1] == (unsigned char)c)
		{
			return ((char *)(s + i - 1));
		}
		i--;
	}
	return (NULL);
}
