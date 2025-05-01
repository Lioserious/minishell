#include "libft.h"
/**
* @brief Sucht das erste Vorkommen eines Zeichens in einem String
*
* Diese Funktion durchsucht den String 's' nach dem ersten Vorkommen des
* Zeichens 'c' (als unsigned char interpretiert). Falls das Zeichen
* gefunden wird,
* gibt die Funktion einen Zeiger auf diese Position zurück. Falls 'c'
* das Nullzeichen
* '\0' ist, wird ein Zeiger auf das Ende des Strings zurückgegeben.
* Falls 's' NULL
* ist oder das Zeichen nicht gefunden wird, wird NULL zurückgegeben.
*
* @param s Der zu durchsuchende String
* @param c Das zu suchende Zeichen (wird als unsigned char interpretiert)
* @return Zeiger auf das erste Vorkommen des Zeichens oder NULL, wenn 
* nicht gefunden
*/
char	*ft_strchr(const char *s, int c)
{
	unsigned char	cc;

	if (!s)
		return (NULL);
	cc = (unsigned char) c;
	while (*s)
	{
		if (*s == cc)
			return ((char *)s);
		s++;
	}
	if (cc == '\0')
		return ((char *)s);
	return (NULL);
}
