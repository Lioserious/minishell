/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:14:42 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:14:42 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prüft, ob ein Wert ein ASCII-Zeichen ist
 *
 * Diese Funktion prüft, ob der übergebene Wert im gültigen
 * ASCII-Bereich (0-127) liegt. Sie ist eine Reimplementierung
 * der Standard-C-Bibliotheksfunktion isascii.
 *
 * @param c Der zu prüfende Wert
 * @return 1, wenn der Wert im ASCII-Bereich liegt, sonst 0
 */
int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
