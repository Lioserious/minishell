/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:30:54 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/10 13:15:40 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Alloziert Speicher und registriert ihn beim Garbage Collector
 *
 * Diese Funktion alloziert Speicher mit der angegebenen Größe mittels malloc()

	* und registriert den allozierten Speicherbereich automatisch beim
	* Garbage Collector.
 * Falls die Speicherallokation fehlschlägt,
	wird eine Fehlermeldung ausgegeben und
 * das Programm mit dem Fehlercode 1 beendet. Der zurückgegebene Speicher wird

	* automatisch vom Garbage Collector verwaltet und muss nicht manuell
	* freigegeben werden.
 *
 * @param size Die Größe des zu allozierenden Speichers in Bytes
 * @return Ein Zeiger auf den allozierten Speicherbereich
 */
void	*gc_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		//ft_putstr_fd("minishell: ", STDERR_FILENO);
		//ft_putstr_fd("Allocation Failed", STDERR_FILENO);
		//ft_putstr_fd("\n", STDERR_FILENO);
		exit(1);
	}
	garbage_collector_add(ptr);
	return (ptr);
}
