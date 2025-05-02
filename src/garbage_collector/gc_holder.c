/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_holder.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:30:32 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:31:53 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Gibt Zugriff auf den internen Garbage Collector Speicher
 *
 * Diese Funktion liefert einen Zeiger auf die statische Liste,
 * die alle Speicheradressen im Garbage Collector verwaltet.
 * Sie wird intern von anderen GC-Funktionen verwendet.
 *
 * @return Zeiger auf die Liste der verwalteten Speicherbereiche
 */
t_list	**garbage_holder(void)
{
	static t_list	*ptr = NULL;

	return (&ptr);
}
