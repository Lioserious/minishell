/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:31:24 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 17:25:00 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char *input;

	while (1)
	{
		input = gc_readline(PROMPT);
		if (!input)
		{
			ft_putendl_fd("exit", STDOUT_FILENO);
			break ;
		}
		if (input[0] == '\0')
			continue ;

		add_history(input);
		if (ft_strncmp(input, "exit", 5) == 0)
			break ;
		else
		{
			ft_putstr_fd("Command entered: ", STDOUT_FILENO);
			ft_putendl_fd(input, STDOUT_FILENO);
		}
	}
	rl_clear_history();
	garbage_collector_empty();
	return (0);
}
