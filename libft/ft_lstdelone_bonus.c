/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:15:19 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:15:19 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Löscht und befreit ein einzelnes Listenelement
 *
 * Diese Funktion löscht den Inhalt des übergebenen Listenelements 'lst'
 * mit der übergebenen Funktion 'del' und gibt dann den Speicher des
 * Listenelements selbst frei. Sie aktualisiert keine Pointer zu diesem
 * Element, die in anderen Teilen der Liste vorhanden sein könnten.
 * Falls 'lst' oder 'del' NULL sind, wird die Funktion ohne Aktionen beendet.
 *
 * @param lst Zeiger auf das zu löschende Listenelement
 * @param del Funktionszeiger auf die Funktion,
	die den Inhalt des Elements löscht
 * @return Keine Rückgabe (void)
 */
void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->content);
	free(lst);
}
