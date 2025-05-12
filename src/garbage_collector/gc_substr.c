/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 13:21:34 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/08 15:50:20 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/**
* @brief Erstellt einen Teilstring aus einem gegebenen String, und gibt Pointer
*			an garbage collector
* Diese Funktion erstellt einen neuen String, der einen Teilstring
* des übergebenen
* Strings 's' darstellt, beginnend am Index 'start' und maximal 'len'
* Zeichen lang.
* Der neue String wird dynamisch alloziert. Falls 's' NULL ist, wird
* NULL zurückgegeben. Falls 'start' größer oder gleich der Länge von
* 's' ist, wird ein leerer String zurückgegeben.
* Falls 'len' plus 'start' größer als die Länge von 's' ist,
* wird der Teilstring bis zum Ende
* von 's' erstellt. Bei einem Speicherfehler während der
* Allokation wird NULL zurückgegeben.
* Der zurückgegebene String muss vom Aufrufer mit free()
* freigegeben werden, wenn er nicht mehr benötigt wird.
*
* @param s Der Quellstring, aus dem der Teilstring erstellt wird
* @param start Der Startindex für den Teilstring im Quellstring
* @param len Die maximale Länge des zu erstellenden Teilstrings
* @return Ein neu allozierter Teilstring oder NULL bei Fehlern
*/
char	*gc_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_s;
	size_t	i;

	if (s == NULL)
		return (NULL);
	if (start >= ft_strlen(s))
		return (gc_strdup(""));
	if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	sub_s = gc_malloc(len + 1);
	if (sub_s == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		sub_s[i] = s[start + i];
		i++;
	}
	sub_s[i] = '\0';
	return (sub_s);
}
