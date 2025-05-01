#include "libft.h"

static int	length(int n)
{
	int	l;

	l = 0;
	if (n == 0)
		return (1);
	if (n == INT_MIN)
		return (11);
	if (n < 0)
	{
		l++;
		n = -n;
	}
	while (n != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

static void	convert(char *ptr, int n, int l)
{
	unsigned int	num;

	num = n;
	if (n < 0)
	{
		*ptr = '-';
		num = -num;
	}
	if (num == 0)
		*ptr = '0';
	ptr[l--] = '\0';
	while (num)
	{
		ptr[l--] = (num % 10) + '0';
		num /= 10;
	}
}

static void	fake_ft_itoa(int n, char *ptr)
{
	int	l;

	l = length(n);
	convert(ptr, n, l);
}

/**
 * @brief Schreibt eine Ganzzahl in einen Dateideskriptor
 *

	* Diese Funktion konvertiert die Ganzzahl 'n' in einen String und
	* schreibt diesen

	* in den angegebenen Dateideskriptor 'fd'. Die Konvertierung erfolgt
	* mit Hilfe der
 * Hilfsfunktion fake_ft_itoa, die die Zahl in das übergebene Pufferarray 'nbr'
 * schreibt. Die Funktion behandelt alle möglichen Integer-Werte, einschließlich
 * negativer Zahlen.
 *
 * @param n Die zu schreibende Ganzzahl
 * @param fd Der Dateideskriptor, in den geschrieben werden soll
 * @return Keine Rückgabe (void)
 */
void	ft_putnbr_fd(int n, int fd)
{
	char	nbr[12];

	fake_ft_itoa(n, nbr);
	write(fd, nbr, ft_strlen(nbr));
}
