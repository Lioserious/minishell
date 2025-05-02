/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:14:47 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:14:47 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prüft, ob ein Zeichen eine Ziffer ist
 *
 * Diese Funktion prüft, ob das übergebene Zeichen eine
 * dezimale Ziffer (0-9) ist. Sie ist eine Reimplementierung
 * der Standard-C-Bibliotheksfunktion isdigit.
 *
 * @param c Der zu prüfende Zeichenwert
 * @return 1, wenn das Zeichen eine Ziffer ist, sonst 0
 */
int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
