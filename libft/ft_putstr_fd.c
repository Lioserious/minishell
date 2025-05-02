#include "libft.h"

/**
 * @brief Schreibt einen String in einen Dateideskriptor
 *

	* Diese Funktion schreibt den String 's' in den angegebenen
	* Dateideskriptor 'fd'.
 * Die Länge des zu schreibenden Strings wird mit ft_strlen ermittelt. Falls 's'
 * NULL ist, kehrt die Funktion sofort zurück, ohne etwas zu schreiben.
 * Es erfolgt keine Fehlerbehandlung für den Fall,
	dass der Schreibvorgang fehlschlägt.
 *
 * @param s Der zu schreibende String
 * @param fd Der Dateideskriptor, in den geschrieben werden soll
 * @return Keine Rückgabe (void)
 */
void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}
