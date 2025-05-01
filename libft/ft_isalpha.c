#include "libft.h"

/**
 * @brief Prüft, ob ein Zeichen ein Buchstabe ist
 *
 * Diese Funktion prüft, ob das übergebene Zeichen ein Buchstabe
 * (A-Z, a-z) ist. Sie ist eine Reimplementierung der
 * Standard-C-Bibliotheksfunktion isalpha.
 *
 * @param c Der zu prüfende Zeichenwert
 * @return 1, wenn das Zeichen ein Buchstabe ist, sonst 0
 */
int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	else
		return (0);
}
