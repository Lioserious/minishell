/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:16:18 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:16:18 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Schreibt ein einzelnes Zeichen in einen Dateideskriptor
 *

	* Diese Funktion schreibt das Zeichen 'c' in den angegebenen
	* Dateideskriptor 'fd'.
 * Sie verwendet die write-Systemfunktion, um genau ein Byte zu schreiben.
 * Es erfolgt keine Fehlerbehandlung für den Fall,
	dass der Schreibvorgang fehlschlägt.
 *
 * @param c Das zu schreibende Zeichen
 * @param fd Der Dateideskriptor, in den geschrieben werden soll
 * @return Keine Rückgabe (void)
 */
void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
