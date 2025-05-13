/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:31:24 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/13 14:04:40 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char			*input;
	t_token_list	*tokens;
	t_cmd_list		*cmd_list;
	t_env_list		*env_list;

	env_list = init_env_list();
	init_env(env_list);
	// Begrüßung anzeigen
	ft_putendl_fd("Welcome to Minishell Test!", STDOUT_FILENO);
	// ft_putendl_fd("First, running automatic test cases...", STDOUT_FILENO);
	// // Automatische Tests für Tokenizer und Parser ausführen
	// run_tokenizer_tests();
	// run_parser_tests();
	// run_env_var_tests();
	// ft_putendl_fd("\nNow entering interactive mode. Type 'exit' to quit.",
	// 	STDOUT_FILENO);
	// ft_putendl_fd("Enter commands to see tokenization and parsing results.",
	// 	STDOUT_FILENO);
	// Interaktiver Modus
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
		// if (ft_strncmp(input, "exit", 5) == 0)
		// 	break ;
		// Tokenize the input and display results
		tokens = tokenizer(input);
		if (!tokens)
		{
			ft_putendl_fd("ERROR: Tokenization failed!", STDOUT_FILENO);
			continue ;
		}
		// ft_putendl_fd("\n--- TOKENIZATION RESULTS ---", STDOUT_FILENO);
		// print_tokenizer_results(tokens);
		// Parse the tokens and display results
		cmd_list = parser(tokens);
		if (!cmd_list)
		{
			ft_putendl_fd("ERROR: Parsing failed!", STDOUT_FILENO);
			continue ;
		}
		// ft_putendl_fd("\n--- PARSING RESULTS ---", STDOUT_FILENO);
		// print_parsed_cmd_list(cmd_list);
		execute(env_list, cmd_list->head);
	}
	rl_clear_history();
	garbage_collector_empty();
	return (0);
}
