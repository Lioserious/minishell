#include "libft.h"

/**

	* @brief Schreibt einen String gefolgt von einem Zeilenumbruch in
	* einen Dateideskriptor
 *

	* Diese Funktion schreibt den String 's' in den angegebenen
	* Dateideskriptor 'fd'
 * und fügt anschließend einen Zeilenumbruch hinzu. Falls 's' NULL ist,
	kehrt die
 * Funktion sofort zurück,
	ohne etwas zu schreiben. Die Funktion nutzt ft_putstr_fd
 * zum Schreiben des Strings und dann write für den Zeilenumbruch.
 *
 * @param s Der zu schreibende String
 * @param fd Der Dateideskriptor, in den geschrieben werden soll
 * @return Keine Rückgabe (void)
 */
void	ft_putendl_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
