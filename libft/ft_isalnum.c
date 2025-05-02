/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:14:31 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:14:31 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Prüft, ob ein Zeichen alphanumerisch ist
 *
 * Diese Funktion prüft, ob das übergebene Zeichen entweder ein Buchstabe
 * (A-Z, a-z) oder eine Ziffer (0-9) ist. Sie ist eine Reimplementierung
 * der Standard-C-Bibliotheksfunktion isalnum.
 *
 * @param c Der zu prüfende Zeichenwert
 * @return 1, wenn das Zeichen alphanumerisch ist, sonst 0
 */
int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
