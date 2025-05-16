/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:31:24 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/16 15:39:55 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	char			*input;
	t_token_list	*tokens;
	t_cmd_list		*cmd_list;
	t_env_list		*env_list;

	(void)argc;
	(void)argv;
	// Umgebungsvariablen initialisieren
	env_list = init_env_list();
	init_env(env_list, env);
	// Begrüßung anzeigen
	ft_putendl_fd("Welcome to Minishell Test!", STDOUT_FILENO);
	ft_putendl_fd("First, running automatic test cases...", STDOUT_FILENO);
	// Automatische Tests für Tokenizer und Parser ausführen
	run_tokenizer_tests();
	run_parser_tests();
	run_env_var_tests();
	ft_putendl_fd("\nNow entering interactive mode. Type 'exit' to quit.",
		STDOUT_FILENO);
	ft_putendl_fd("Enter commands to see tokenization and parsing results.",
		STDOUT_FILENO);
	// Interaktiver Modus
	terminal_setup();
	signal_setup();
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
		// Tokenize the input with environment list and display results
		tokens = tokenizer(input, env_list);
		if (!tokens)
		{
			ft_putendl_fd("ERROR: Tokenization failed!", STDOUT_FILENO);
			continue ;
		}
		ft_putendl_fd("\n--- TOKENIZATION RESULTS ---", STDOUT_FILENO);
		print_tokenizer_results(tokens);
		// Parse the tokens and display results
		cmd_list = parser(tokens);
		if (!cmd_list)
		{
			ft_putendl_fd("ERROR: Parsing failed!", STDOUT_FILENO);
			continue ;
		}
		ft_putendl_fd("\n--- PARSING RESULTS ---", STDOUT_FILENO);
		print_parsed_cmd_list(cmd_list);
		// Hier könnte später die Ausführung hinzugefügt werden
		// execute(env_list, cmd_list->head);
	}
	clean_exit(1);
	return (0);
}
