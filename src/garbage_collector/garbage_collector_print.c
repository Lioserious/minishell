/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector_print.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:30:02 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/26 13:27:55 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Zeigt Informationen über alle verwalteten Speicherbereiche an
 *
 * Diese Funktion gibt Debugging-Informationen über alle im
 * Garbage Collector verwalteten Speicherbereiche aus.
 * Nützlich zur Fehlersuche bei Speicherproblemen und zum Überprüfen
 * des Inhalts der verwalteten Speicherbereiche.
 */
void	garbage_collector_print(void)
{
	t_list	*temp;
	size_t	i;

	temp = *garbage_holder();
	i = 0;
	while (temp != NULL)
	{
		printf("Pointer %zu: %p, %s\n", i, temp->content,
			(char *)temp->content);
		temp = temp->next;
		i++;
	}
}
