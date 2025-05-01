#include "libft.h"
/**
* @brief Berechnet die Länge eines Strings
*
* Diese Funktion zählt die Anzahl der Zeichen in einem String 's' bis zum 
* ersten Null-Terminator ('\0'). Falls 's' NULL ist, wird 0 zurückgegeben.
* Die Funktion zählt den Null-Terminator selbst nicht mit.
*
* @param s Der zu messende String
* @return Die Anzahl der Zeichen im String (ohne Null-Terminator)
*/
size_t	ft_strlen(const char *s)
{
	size_t	counter;

	counter = 0;
	if (s)
	{
		while (s[counter])
			counter++;
	}
	return (counter);
}
