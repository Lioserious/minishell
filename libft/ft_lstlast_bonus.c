/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:15:29 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:15:29 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Findet das letzte Element einer verketteten Liste
 *
 * Diese Funktion durchläuft die verkettete Liste 'lst' und gibt
 * einen Zeiger

	* auf das letzte Element zurück. Das letzte Element ist definiert
	* als das Element,

	* dessen 'next'-Zeiger NULL ist. Falls die Liste leer ist
	* (d.h. 'lst' ist NULL),
 * wird NULL zurückgegeben.
 *
 * @param lst Zeiger auf den Anfang der verketteten Liste
 * @return Zeiger auf das letzte Element der Liste oder NULL,
	wenn die Liste leer ist
 */
t_list	*ft_lstlast(t_list *lst)
{
	t_list	*current;

	current = lst;
	if (current == NULL)
		return (NULL);
	while (current->next != NULL)
		current = current->next;
	return (current);
}
