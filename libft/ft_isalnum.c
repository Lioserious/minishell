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
