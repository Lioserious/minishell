#include "libft.h"

/**
 * @brief Wendet eine Funktion auf alle Elemente einer verketteten Liste an
 *
 * Diese Funktion durchläuft die gesamte verkettete Liste 'lst' und wendet
 * die übergebene Funktion 'f' auf den Inhalt jedes Elements an. Die Liste
 * selbst wird nicht verändert, nur die Inhalte der Elemente können durch
 * die Funktion 'f' modifiziert werden.
 *
 * @param lst Zeiger auf den Anfang der zu verarbeitenden verketteten Liste
 * @param f Funktionszeiger auf die Funktion,
	die auf jeden Inhalt angewendet wird
 * @return Keine Rückgabe (void)
 */
void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		f(current->content);
		current = current->next;
	}
}
