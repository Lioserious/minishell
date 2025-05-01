#include "libft.h"

/**
 * @brief Berechnet die Länge einer verketteten Liste
 *
 * Diese Funktion durchläuft die verkettete Liste 'lst' und zählt die Anzahl

	* der Elemente in der Liste. Die Funktion gibt die Gesamtanzahl
	* der Elemente zurück.
 * Falls die Liste leer ist (d.h. 'lst' ist NULL), wird 0 zurückgegeben.
 *
 * @param lst Zeiger auf den Anfang der verketteten Liste
 * @return Die Anzahl der Elemente in der Liste
 */
int	ft_lstsize(t_list *lst)
{
	t_list	*current;
	int		count;

	current = lst;
	count = 0;
	while (current != NULL)
	{
		current = current->next;
		count++;
	}
	return (count);
}
