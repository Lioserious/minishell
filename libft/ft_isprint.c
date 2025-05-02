/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:14:52 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:14:52 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prüft, ob ein Zeichen druckbar ist
 *
 * Diese Funktion prüft, ob das übergebene Zeichen ein druckbares
 * ASCII-Zeichen ist (Werte 32-126, einschließlich Leerzeichen).
 * Sie ist eine Reimplementierung der Standard-C-Bibliotheksfunktion isprint.
 *
 * @param c Der zu prüfende Zeichenwert
 * @return 1, wenn das Zeichen druckbar ist, sonst 0
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
