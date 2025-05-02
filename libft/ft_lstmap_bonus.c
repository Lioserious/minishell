/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:15:34 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:15:34 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_list(t_list *lst, void (*del)(void *))
{
	t_list	*p_h;

	while (lst != NULL)
	{
		p_h = lst->next;
		del(lst->content);
		free(lst);
		lst = p_h;
	}
}

static t_list	*create_new_n(void *(*f)(void *), void *content,
		void (*del)(void *))
{
	t_list	*new_n;

	new_n = (t_list *)malloc(sizeof(t_list));
	if (new_n == NULL)
		return (NULL);
	new_n->content = f(content);
	if (new_n->content == NULL)
	{
		del(new_n);
		free(new_n);
		return (NULL);
	}
	new_n->next = NULL;
	return (new_n);
}

/**

	* @brief Erstellt eine neue Liste durch Anwendung einer Funktion
	* auf alle Elemente
 *

	* Diese Funktion durchläuft die verkettete Liste 'lst' und
	* erstellt eine neue Liste,

	* deren Elemente durch Anwendung der Funktion 'f' auf den Inhalt
	* jedes Elements der
 * Originalliste entstehen. Die Funktion 'del' wird verwendet,
	um bei einem Fehler

	* die bereits erstellten Elemente zu löschen. Falls ein Element
	* nicht erstellt werden
 * kann (z.B. wegen Speichermangel),
	wird die gesamte neue Liste gelöscht und NULL
 * zurückgegeben.
 *
 * @param lst Zeiger auf den Anfang der Originalliste
 * @param f Funktionszeiger auf die Funktion, die den Inhalt
 * transformiert
 * @param del Funktionszeiger auf die Funktion,
	die bei einem Fehler den Inhalt löscht
 * @return Zeiger auf den Anfang der neuen Liste oder NULL
 * bei einem Fehler
 */
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_l;
	t_list	*new_n;
	t_list	*prev_n;
	t_list	*current;

	new_l = NULL;
	prev_n = NULL;
	current = lst;
	while (current != NULL)
	{
		new_n = create_new_n(f, current->content, del);
		new_n->next = NULL;
		if (new_n == NULL)
		{
			free_list(new_l, del);
			return (NULL);
		}
		if (new_l == NULL)
			new_l = new_n;
		else
			prev_n->next = new_n;
		prev_n = new_n;
		current = current->next;
	}
	return (new_l);
}
