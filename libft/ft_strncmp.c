#include "libft.h"
/**
* @brief Vergleicht zwei Strings bis zu einer bestimmten Länge
*
* Diese Funktion vergleicht die ersten 'n' Zeichen der Strings 's1' und 's2'.
* Der Vergleich erfolgt byte-weise und verwendet den Wert der unsigned
* char-Darstellung der Zeichen. Falls alle verglichenen Zeichen gleich sind
* oder 'n' Zeichen verglichen wurden,
* wird 0 zurückgegeben. Andernfalls wird die Differenz zwischen den ersten
* unterschiedlichen
* Zeichen (als unsigned char betrachtet) zurückgegeben.
*
* @param s1 Der erste zu vergleichende String
* @param s2 Der zweite zu vergleichende String
* @param n Die maximale Anzahl der zu vergleichenden Zeichen
* @return 0, falls die ersten 'n' Zeichen identisch sind oder 'n' 0 ist.
*         Ansonsten die Differenz zwischen den ersten unterschiedlichen Zeichen,
*         wobei 's1[i] - s2[i]' zurückgegeben wird.
*/
int	ft_strncmp(const char *s1, const char *s2, size_t n)
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
		if (s_o[i] == '\0' || s_t[i] == '\0')
			break ;
		i++;
	}
	return (0);
}
