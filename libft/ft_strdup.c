/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:16:50 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:16:50 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
* @brief Erstellt eine Kopie eines Strings
*
* Diese Funktion erstellt eine Kopie des Strings 's' und alloziert dafür
* dynamisch Speicher. Die Kopie ist ein neuer String, der an einer anderen
* Speicheradresse liegt, aber den gleichen Inhalt wie das Original hat.
* Falls 's' NULL ist, wird NULL zurückgegeben. Bei einem Speicherfehler während
* der Allokation wird ebenfalls NULL zurückgegeben. Der zurückgegebene String
* muss vom Aufrufer mit free() freigegeben werden, wenn er nicht mehr
* benötigt wird.
*
* @param s Der zu duplizierende String
* @return Ein neu allozierter String mit dem gleichen Inhalt oder NULL
* bei Fehlern
*/
char	*ft_strdup(const char *s)
{
	char	*ptr;
	size_t	len;
	size_t	i;

	if (!s)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (!ptr)
		return (NULL);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[len] = '\0';
	return (ptr);
}
