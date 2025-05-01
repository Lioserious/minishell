#include "libft.h"
/**
* @brief Konvertiert einen Großbuchstaben in einen Kleinbuchstaben
*
* Diese Funktion konvertiert einen Großbuchstaben (A-Z) in den entsprechenden
* Kleinbuchstaben (a-z). Falls der übergebene Wert kein Großbuchstabe ist,
* wird er unverändert zurückgegeben.
*
* @param c Der zu konvertierende Zeichen-Code
* @return Der konvertierte Zeichen-Code (Kleinbuchstabe) oder der
*		unveränderte Wert,falls 'c' kein Großbuchstabe ist
*/
int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	else
		return (c);
}
