/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:17:18 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:17:18 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
* @brief Erstellt einen neuen String durch Anwendung einer Funktion auf jeden
* Zeichen
* Diese Funktion durchläuft jeden Zeichen des Strings 's' und wendet
* die übergebene Funktion 'f' auf jeden Zeichen an. Die Funktion 'f'
* erhält den Index des aktuellen Zeichens und das Zeichen selbst als Parameter.
* Das Ergebnis jeder Funktionsanwendung wird in einem neu allozierten String
* an der entsprechenden Position gespeichert. Falls 's' NULL ist oder die
* Speicherallokation fehlschlägt, wird NULL zurückgegeben.
* Der zurückgegebene String muss vom Aufrufer mit free() freigegeben werden,
* wenn er nicht mehr benötigt wird.
*
* @param s Der Quellstring, auf dessen Zeichen die Funktion angewendet wird
* @param f Die Funktion, die auf jedes Zeichen angewendet wird.
*          Sie erhält den Index und das aktuelle Zeichen und gibt ein neues
			Zeichen zurück.
* @return Ein neu allozierter String mit den Ergebnissen der 
		 Funktionsanwendungen oder NULL bei Fehlern
*/
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*ptr;
	unsigned int	i;

	if (s == NULL)
		return (NULL);
	ptr = malloc(ft_strlen(s) + 1);
	if (ptr == NULL)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
