/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 16:02:30 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/15 20:28:15 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env.h"

// MUSS NOCH RAUS
void print_parsed_cmd_list(t_cmd_list *cmd_list)
{
    t_cmd_node *current;
    t_file_node *file;
    int i;

    if (!cmd_list)
    {
        printf("Empty command list\n");
        return;
    }
    
    printf("Command list with %zd command(s):\n", cmd_list->size);
    current = cmd_list->head;
    
    while (current)
    {
        printf("Command Type: %d\n", current->cmd_type);
        
        // Befehl und Argumente anzeigen
        if (current->cmd)
        {
            i = 0;
            printf("  Args: ");
            while (current->cmd[i])
            {
                printf("[%s] ", current->cmd[i]);
                i++;
            }
            printf("\n");
        }
        
        // Redirections anzeigen
        if (current->file && current->file->size > 0)
        {
            printf("  Redirections (%zd):\n", current->file->size);
            file = current->file->head;
            while (file)
            {
                printf("    Type: %d, File: [%s]\n", 
                       file->redirection_type, file->name);
                file = file->next;
            }
        }
        
        current = current->next;
        printf("-----------------\n");
    }
}

void	run_parser_tests(void)
{
	const char		*test_cases[] = {"echo hello", "ls -la | grep .c",
				"echo test > output.txt",
				"cat < input.txt | sort | uniq > result.txt", NULL};
	int				i;
	t_token_list	*tokens;
	t_cmd_list		*cmd_list;
	char			*input_copy;
    t_env_list      *env_list;
    extern char     **environ;

    // Erstelle Umgebungsvariablen-Liste für die Tests
    env_list = init_env_list();
    init_env(env_list, environ);

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
		
		// Tokenize input mit Umgebungsvariablen
		tokens = tokenizer(input_copy, env_list);
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
    t_env_list *env_list;
    extern char **environ;
    
    // Erstelle Umgebungsvariablen-Liste für die Tests
    env_list = init_env_list();
    init_env(env_list, environ);
    
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
        
        // Tokenize input mit Umgebungsvariablen
        tokens = tokenizer(input_copy, env_list);
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
