/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:18:05 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:18:05 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/**
* @brief Konvertiert einen Kleinbuchstaben in einen Großbuchstaben
*
* Diese Funktion konvertiert einen Kleinbuchstaben (a-z) in den entsprechenden
* Großbuchstaben (A-Z). Falls der übergebene Wert kein Kleinbuchstabe ist,
* wird er unverändert zurückgegeben.
*
* @param c Der zu konvertierende Zeichen-Code
* @return Der konvertierte Zeichen-Code (Großbuchstabe) oder der
*			unveränderte Wert, falls 'c' kein Kleinbuchstabe ist
*/
int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	else
		return (c);
}
