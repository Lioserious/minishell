#include "libft.h"

/**
 * @brief Setzt einen Speicherbereich auf Null
 *
 * Diese Funktion setzt 'len' Bytes des Speicherbereichs, auf den 's' zeigt,
 * auf den Wert Null (0). Sie ist eine vereinfachte Version der memset-Funktion
 * und wird typischerweise verwendet,
	um Speicher zu initialisieren oder zu löschen.
 *
 * @param s Zeiger auf den zu löschenden Speicherbereich
 * @param len Anzahl der zu löschenden Bytes
 */

void	ft_bzero(void *s, size_t len)
{
	ft_memset(s, 0, len);
}
