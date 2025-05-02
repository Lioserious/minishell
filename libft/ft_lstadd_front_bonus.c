/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:15:07 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:15:07 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Fügt ein neues Element am Anfang einer verketteten Liste hinzu
 *

	* Diese Funktion fügt das Element 'new' am Anfang der verketteten
	* Liste 'lst' hinzu.

	* Der Zeiger 'next' des neuen Elements wird auf den aktuellen
	* Listenanfang gesetzt,
 * und dann wird der Listenanfang-Zeiger aktualisiert,
	um auf das neue Element zu zeigen.

	* Die Funktion ändert den Anfang der Liste in-place durch den
	* Doppelzeiger 'lst'.
 *
 * @param lst Doppelzeiger auf den Anfang der verketteten Liste
 * @param new Das neue Element, das am Anfang der Liste eingefügt werden soll
 * @return Keine Rückgabe (void)
 */
void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
