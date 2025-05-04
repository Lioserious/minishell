/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:31:24 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 16:50:36 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char			*input;
	t_token_list	*tokens;

	// Run automatic tests first
	ft_putendl_fd("Welcome to Minishell Tokenizer Test!", STDOUT_FILENO);
	ft_putendl_fd("First, running automatic test cases...", STDOUT_FILENO);
	run_tokenizer_tests();
	
	ft_putendl_fd("\nNow entering interactive mode. Type 'exit' to quit.", STDOUT_FILENO);
	ft_putendl_fd("Enter commands to see how they are tokenized.", STDOUT_FILENO);
	
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
		
		// Tokenize the input and display results
		tokens = tokenizer(input);
		if (tokens)
		{
			print_tokenizer_results(tokens);
		}
		else
		{
			ft_putendl_fd("ERROR: Tokenization failed!", STDOUT_FILENO);
		}
	}
	
	rl_clear_history();
	garbage_collector_empty();
	return (0);
}
