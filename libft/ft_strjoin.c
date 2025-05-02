/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:16:58 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:16:58 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**

@brief Verbindet zwei Strings zu einem neuen String

*Diese Funktion erstellt einen neuen String, der aus der Verkettung von 's1'
* und 's2' besteht.
* Der neue String wird dynamisch alloziert. Falls sowohl 's1' als auch 's2'
* NULL sind,
* wird NULL zurückgegeben. Falls nur einer der beiden Strings NULL ist,
* wird der andere
* String kopiert. Bei einem Speicherfehler während der Allokation wird ebenfalls
* NULL zurückgegeben.
* Der zurückgegebene String muss vom Aufrufer mit free() freigegeben werden,
* wenn er nicht mehr
*benötigt wird.

@param s1 Der erste zu verbindende String (oder NULL)
@param s2 Der zweite zu verbindende String (oder NULL)
@return Ein neu allozierter String mit der Verkettung von s1 und s2,
* oder NULL bei Fehlern
*/
char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	char	*save;
	size_t	len1;
	size_t	len2;

	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len1 = ft_strlen(s1);
	else
		len1 = 0;
	if (s2)
		len2 = ft_strlen(s2);
	else
		len2 = 0;
	s = malloc(len1 + len2 + 1);
	if (!s)
		return (NULL);
	save = s;
	while (s1 && *s1)
		*s++ = *s1++;
	while (s2 && *s2)
		*s++ = *s2++;
	*s = '\0';
	return (save);
}
