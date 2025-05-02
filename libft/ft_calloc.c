/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:14:22 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:14:22 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Allokiert und initialisiert Speicher
 *
 * Diese Funktion allokiert Speicher für 'num' Elemente der Größe 'size'
 * und initialisiert den allozierten Speicher mit Nullen. Sie ist eine
 * Reimplementierung der Standard-C-Bibliotheksfunktion calloc.
 *
 * @param num Anzahl der zu allozierenden Elemente
 * @param size Größe jedes Elements in Bytes
 * @return Zeiger auf den allozierten Speicher oder NULL bei Fehler
 */
void	*ft_calloc(size_t num, size_t size)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = malloc(num * size);
	if (ptr == NULL)
	{
		return (NULL);
	}
	i = 0;
	while (i < (num * size))
	{
		ptr[i] = 0;
		i++;
	}
	return (ptr);
}
