/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:16:54 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:16:54 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
* @brief Wendet eine Funktion auf jeden Zeichen eines Strings an
*
* Diese Funktion durchläuft jeden Zeichen des Strings 's' und wendet die 
* übergebene Funktion 'f' auf jeden Zeichen an. Der Funktion 'f' werden dabei 
* der Index des aktuellen Zeichens und ein Zeiger auf das aktuelle Zeichen 
* übergeben. Falls 's' oder 'f' NULL ist, wird keine Operation durchgeführt.
* Die Funktion verändert den Original-String direkt, da 'f' Zugriff auf 
* die Zeiger der einzelnen Zeichen erhält.
*
* @param s Der zu bearbeitende String
* @param f Die Funktion, die auf jedes Zeichen angewendet wird. 
*          Sie erhält den Index und einen Zeiger auf das aktuelle Zeichen.
* @return Nichts (void)
*/
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	while (s[i] != '\0')
	{
		f(i, &s[i]);
		i++;
	}
}
