/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:38:41 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 13:45:09 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// eigene readline implementierung, die den input Pointer direkt in den GC
// anhaengt.
char	*gc_readline(const char *prompt)
{
	char *input;

	input = readline(prompt);
	if (input)
		garbage_collector_add(input);
	return (input);
}