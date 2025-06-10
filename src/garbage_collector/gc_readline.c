/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:38:41 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/10 13:32:12 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// eigene readline implementierung, die den input Pointer direkt in den GC
// anhaengt.
char	*gc_readline(const char *prompt)
{
	char	*input;
	if (isatty(fileno(stdin)))
		input = readline(PROMPT);
	else
	{
		char *line;
		line = get_next_line(fileno(stdin));
		input = ft_strtrim(line, "\n");
		free(line);
	}
	input = readline(prompt);
	if (input)
		garbage_collector_add(input);
	return (input);
}
