/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:31:24 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/12 15:00:33 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	run_parser_tests(void)
{
	const char		*test_cases[] = {"echo hello", "ls -la | grep .c",
				"echo test > output.txt",
				"cat < input.txt | sort | uniq > result.txt", NULL};
	int				i;
	t_token_list	*tokens;
	t_cmd_list		*cmd_list;
	char			*input_copy;

	i = 0;
	ft_putendl_fd("\n--- PARSER TEST CASES ---", STDOUT_FILENO);
	while (test_cases[i])
	{
		ft_putstr_fd("\nTest Case #", STDOUT_FILENO);
		ft_putnbr_fd(i + 1, STDOUT_FILENO);
		ft_putstr_fd(": '", STDOUT_FILENO);
		ft_putstr_fd((char *)test_cases[i], STDOUT_FILENO);
		ft_putendl_fd("'", STDOUT_FILENO);
		
		// Kopie des Strings erstellen und dann tokenizieren
		input_copy = gc_strdup(test_cases[i]);
		if (!input_copy)
		{
			ft_putendl_fd("Memory allocation failed!", STDOUT_FILENO);
			i++;
			continue;
		}
		
		// Tokenize input
		tokens = tokenizer(input_copy);
		if (!tokens)
		{
			ft_putendl_fd("Tokenization failed!", STDOUT_FILENO);
			i++;
			continue;
		}
		
		ft_putendl_fd("\n--- TOKENIZATION RESULTS ---", STDOUT_FILENO);
		print_tokenizer_results(tokens);
		
		// Parse tokens
		cmd_list = parser(tokens);
		if (!cmd_list)
		{
			ft_putendl_fd("Parsing failed!", STDOUT_FILENO);
			i++;
			continue;
		}
		
		// Display parsed command structure
		ft_putendl_fd("\n--- PARSING RESULTS ---", STDOUT_FILENO);
		print_parsed_cmd_list(cmd_list);
		i++;
	}
}

void run_env_var_tests(void)
{
    const char *test_cases[] = {
        "echo $HOME",                     // Einfache Umgebungsvariable
        "echo $USER is the current user", // Variable mit umgebendem Text
        "echo $PATH",                     // Lange Variable mit Pfaden
        "echo $?",                        // Exit-Status-Variable
        "echo \"$HOME\"",                 // Variable in doppelten Anführungszeichen (sollte expandiert werden)
        "echo '$HOME'",                   // Variable in einfachen Anführungszeichen (sollte NICHT expandiert werden)
        "echo $NONEXISTENT",              // Nicht existierende Variable
        "cd $HOME",                       // Variable als Argument für einen Builtin
        "ls $HOME/Documents",             // Variable als Teil eines Pfades
        "echo $HOME > output.txt",        // Variable mit Redirection
        "echo $HOME | grep /home",        // Variable mit Pipe
        "echo \"The home is $HOME\"",     // Variable inmitten von Text in doppelten Anführungszeichen
        NULL
    };
    
    int i = 0;
    t_token_list *tokens;
    t_cmd_list *cmd_list;
    char *input_copy;
    
    ft_putendl_fd("\n--- ENVIRONMENT VARIABLE TEST CASES ---", STDOUT_FILENO);
    
    while (test_cases[i])
    {
        ft_putstr_fd("\nTest Case #", STDOUT_FILENO);
        ft_putnbr_fd(i + 1, STDOUT_FILENO);
        ft_putstr_fd(": '", STDOUT_FILENO);
        ft_putstr_fd((char *)test_cases[i], STDOUT_FILENO);
        ft_putendl_fd("'", STDOUT_FILENO);
        
        // Kopie des Strings erstellen und dann tokenizieren
        input_copy = gc_strdup(test_cases[i]);
        if (!input_copy)
        {
            ft_putendl_fd("Memory allocation failed!", STDOUT_FILENO);
            i++;
            continue;
        }
        
        // Tokenize input
        tokens = tokenizer(input_copy);
        if (!tokens)
        {
            ft_putendl_fd("Tokenization failed!", STDOUT_FILENO);
            i++;
            continue;
        }
        
        ft_putendl_fd("\n--- TOKENIZATION RESULTS ---", STDOUT_FILENO);
        print_tokenizer_results(tokens);
        
        // Parse tokens
        cmd_list = parser(tokens);
        if (!cmd_list)
        {
            ft_putendl_fd("Parsing failed!", STDOUT_FILENO);
            i++;
            continue;
        }
        
        // Display parsed command structure
        ft_putendl_fd("\n--- PARSING RESULTS ---", STDOUT_FILENO);
        print_parsed_cmd_list(cmd_list);
        i++;
    }
}

int	main(void)
{
	char			*input;
	t_token_list	*tokens;
	t_cmd_list		*cmd_list;

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
	}
	rl_clear_history();
	garbage_collector_empty();
	return (0);
}
