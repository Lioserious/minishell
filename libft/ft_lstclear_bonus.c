/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:15:12 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:15:12 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Löscht und befreit eine gesamte verkettete Liste
 *
 * Diese Funktion durchläuft alle Elemente der verketteten Liste 'lst',
 * löscht den Inhalt jedes Elements mit der übergebenen Funktion 'del'
 * und gibt dann den Speicher für jedes Listenelement frei. Am Ende wird
 * der Listenanfang auf NULL gesetzt, um eine leere Liste zu kennzeichnen.
 * Falls 'lst', '*lst' oder 'del' NULL sind,
	wird die Funktion ohne Aktionen beendet.
 *
 * @param lst Doppelzeiger auf den Anfang der zu löschenden verketteten Liste
 * @param del Funktionszeiger auf die Funktion,
	die den Inhalt jedes Elements löscht
 * @return Keine Rückgabe (void)
 */
void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*next;

	if (lst == NULL || *lst == NULL || del == NULL)
		return ;
	current = *lst;
	while (current != NULL)
	{
		next = current->next;
		del(current->content);
		free(current);
		current = next;
	}
	*lst = NULL;
}
