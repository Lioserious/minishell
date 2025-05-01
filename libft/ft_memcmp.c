#include "libft.h"

/**
 * @brief Vergleicht zwei Speicherbereiche
 *
 * Diese Funktion vergleicht die ersten 'n' Bytes der Speicherbereiche, auf die
 * 's1' und 's2' zeigen,
	byteweise miteinander. Der Vergleich erfolgt lexikografisch,

	* wobei jedes Byte als unsigned char behandelt wird. 
	* Die Funktion gibt einen Wert
 * zurück, der angibt, ob der erste Speicherbereich kleiner, gleich oder größer
 * als der zweite ist.
 *
 * @param s1 Zeiger auf den ersten zu vergleichenden Speicherbereich
 * @param s2 Zeiger auf den zweiten zu vergleichenden Speicherbereich
 * @param n Die Anzahl der zu vergleichenden Bytes
 * @return (Integer < 0, wenn s1 < s2); Integer = 0, wenn s1 = s2; Integer > 0,
	wenn s1 > s2
 */
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s_o;
	unsigned char	*s_t;
	size_t			i;

	s_o = (unsigned char *)s1;
	s_t = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s_o[i] != s_t[i])
			return (s_o[i] - s_t[i]);
		i++;
	}
	return (0);
}
