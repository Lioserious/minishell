#include "libft.h"

/**
 * @brief Prüft, ob ein Zeichen druckbar ist
 *
 * Diese Funktion prüft, ob das übergebene Zeichen ein druckbares
 * ASCII-Zeichen ist (Werte 32-126, einschließlich Leerzeichen).
 * Sie ist eine Reimplementierung der Standard-C-Bibliotheksfunktion isprint.
 *
 * @param c Der zu prüfende Zeichenwert
 * @return 1, wenn das Zeichen druckbar ist, sonst 0
 */
int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
		return (1);
	else
		return (0);
}
