/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:16:03 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:16:03 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Kopiert einen Speicherbereich in einen anderen
 *
 * Diese Funktion kopiert 'n' Bytes vom Quellspeicherbereich 'src' zum

	* Zielspeicherbereich 'dest'. Die Speicherbereiche dürfen
	* sich nicht überlappen.
 * Falls beide Zeiger NULL sind, wird NULL zurückgegeben, ohne dass eine Kopie
 * stattfindet. Die Funktion gibt einen Zeiger auf den Zielbereich zurück.
 *
 * @param dest Zeiger auf den Zielspeicherbereich
 * @param src Zeiger auf den Quellspeicherbereich
 * @param n Die Anzahl der zu kopierenden Bytes
 * @return Zeiger auf den Zielspeicherbereich (dest)
 */
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (NULL);
	s = (const unsigned char *)src;
	d = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
