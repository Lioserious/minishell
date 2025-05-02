#include "libft.h"

/**
 * @brief Sucht nach einem Byte in einem Speicherbereich
 *
 * Diese Funktion durchsucht die ersten 'n' Bytes des Speicherbereichs, auf den
 * 's' zeigt, nach dem ersten Vorkommen des Bytes 'c'. Der Wert von 'c' wird als
 * unsigned char interpretiert. Die Suche erfolgt byteweise und behandelt den
 * Speicherbereich als Folge von unsigned char-Werten.
 *
 * @param s Zeiger auf den zu durchsuchenden Speicherbereich
 * @param c Der zu suchende Wert (wird als unsigned char interpretiert)
 * @param n Die Anzahl der zu untersuchenden Bytes
 * @return Zeiger auf das erste Vorkommen des Bytes oder NULL,
	wenn es nicht gefunden wurde
 */
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*src;
	size_t			i;

	src = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (src[i] == (unsigned char)c)
			return (src + i);
		i++;
	}
	return (NULL);
}
