/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_add.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:53 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:31:43 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Fügt einen Speicherbereich zum Garbage Collector hinzu
 *
 * Diese Funktion registriert einen dynamisch allozierten Speicherbereich
 * im Garbage Collector, damit er später automatisch freigegeben werden kann.
 *
 * @param ptr Der zu verwaltende Speicherbereich (von malloc, calloc, etc.)
 */
void	garbage_collector_add(void *ptr)
{
	t_list	*neu;

	neu = ft_lstnew(ptr);
	if (!neu)
		error_handler("MEMORY ALLOCATION FAILED: GARBAGE COLLECTOR", 2);
	ft_lstadd_front(garbage_holder(), neu);
}
