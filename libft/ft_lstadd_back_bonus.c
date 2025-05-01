#include "libft.h"

/**
 * @brief Fügt ein neues Element am Ende einer verketteten Liste hinzu
 *

	* Diese Funktion fügt das Element 'new' am Ende der verketteten
	* Liste 'lst' hinzu.
 * Falls die Liste leer ist (d.h. *lst ist NULL), wird 'new' als erstes Element

	* der Liste gesetzt. Andernfalls wird die Liste bis zum letzten Element
	* durchlaufen
 * und 'new' als nächstes Element des letzten Elements hinzugefügt.
 *
 * @param lst Doppelzeiger auf den Anfang der verketteten Liste
 * @param new Das neue Element, das am Ende der Liste eingefügt werden soll
 * @return Keine Rückgabe (void)
 */
void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*content;

	content = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (content->next != NULL)
		content = content->next;
	content->next = new;
}
