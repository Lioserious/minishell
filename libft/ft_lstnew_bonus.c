/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:15:40 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:15:40 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Erstellt ein neues Listenelement
 *
 * Diese Funktion erstellt ein neues Listenelement mit dem übergebenen Inhalt.

	* Der Speicher für das neue Element wird dynamisch alloziert.
	* Der 'content'-Zeiger
 * wird direkt übernommen (keine Kopie des Inhalts erstellt),
	und der 'next'-Zeiger
 * wird auf NULL gesetzt, um anzuzeigen,
	dass dieses Element derzeit nicht mit anderen
 * Elementen verbunden ist.
 *
 * @param content Zeiger auf den Inhalt,
	der im neuen Listenelement gespeichert werden soll

	* @return Zeiger auf das neu erstellte Listenelement oder NULL
	* bei einem Speicherfehler
 */
t_list	*ft_lstnew(void *content)
{
	t_list	*n_node;

	n_node = malloc(sizeof(t_list));
	if (n_node == NULL)
		return (NULL);
	n_node->content = content;
	n_node->next = NULL;
	return (n_node);
}
