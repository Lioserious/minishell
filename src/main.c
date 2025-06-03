/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:31:24 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/03 20:11:12 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initializes the shell environment and terminal settings
 * @param env System environment variables
 * @return Initialized environment list
 */
static t_env_list	*init_shell_environment(char **env)
{
	t_env_list	*env_list;
	t_term		*terminal;

	env_list = init_env_list();
	if (!env_list)
		error_handler("Failed to initialize environment list", 1);
	init_env(env_list, env);
	update_shlvl(env_list);
	terminal = gc_malloc(sizeof(t_term));
	if (!terminal)
		error_handler("Failed to allocate terminal structure", 1);
	terminal_setup(terminal);
	rl_catch_signals = 0;
	signal_setup();
	return (env_list);
}

/**
 * @brief Processes a single input line through tokenization and parsing
 * @param input User input string
 * @param env_list Environment variables list
 * @return Command list ready for execution, or NULL on error
 */
static t_cmd_list *process_input_line(char *input, t_env_list *env_list)
{
   t_token_list *tokens;
   t_cmd_list *cmd_list;

   if (!input || input[0] == '\0')
   	return (NULL);
   add_history(input);
   tokens = tokenizer(input, env_list);
   if (!tokens)
   {
   	ft_putendl_fd("ERROR: Tokenization failed!", STDERR_FILENO);
   	return (NULL);
   }
   cmd_list = parser(tokens);
   if (!cmd_list)
   	return (NULL);
   return (cmd_list);
}
/**
 * @brief Handles user input and command execution in the main loop
 * @param env_list Environment variables list
 * @return 1 to continue loop, 0 to exit
 */
static int handle_user_input(t_env_list *env_list)
{
   char *input;
   t_cmd_list *cmd_list;

   input = gc_readline(PROMPT);
   if (!input)
   {
   	ft_putendl_fd("exit", STDOUT_FILENO);
   	return (0);
   }
   if (input[0] == '\0')
   	return (1);
   cmd_list = process_input_line(input, env_list);
   if (cmd_list && cmd_list->head)
   	execute(env_list, cmd_list->head);
   return (1);
}

/**
 * @brief Main shell loop - reads input and executes commands
 * @param env_list Environment variables list
 */
static void	shell_main_loop(t_env_list *env_list)
{
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTSTP, SIG_IGN);
		if (!handle_user_input(env_list))
			break ;
	}
}

/**
 * @brief Main function - entry point of the minishell program
 * @param argc Argument count (unused)
 * @param argv Argument vector (unused)
 * @param env Environment variables
 * @return Exit status
 */
int	main(int argc, char **argv, char **env)
{
	t_env_list	*env_list;

	(void)argc;
	(void)argv;
	env_list = init_shell_environment(env);
	shell_main_loop(env_list);
	clean_exit(0);
	return (0);
}
