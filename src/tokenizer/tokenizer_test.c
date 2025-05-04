/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_test.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 16:51:06 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 16:51:40 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:31:24 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 17:00:00 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Print token type as string
const char *get_token_type_str(t_token_type type)
{
	static const char *token_type_strings[] = {
		"TOKEN_WORD",
		"TOKEN_PIPE",
		"TOKEN_REDIR_IN",
		"TOKEN_REDIR_OUT",
		"TOKEN_REDIR_APPEND",
		"TOKEN_REDIR_HEREDOC",
		"TOKEN_ENV_VAR",
		"TOKEN_EOF"
	};
	
	if (type >= 0 && type < 8)
		return (token_type_strings[type]);
	return ("UNKNOWN_TOKEN");
}

// Print tokenizer results for testing
void	print_tokenizer_results(t_token_list *tokens)
{
	t_token	*current;
	int		i;

	if (!tokens || !tokens->head)
	{
		ft_putendl_fd("No tokens to display", STDOUT_FILENO);
		return;
	}

	ft_putstr_fd("\n--- Tokenizer Results ---\n", STDOUT_FILENO);
	ft_putstr_fd("Total tokens: ", STDOUT_FILENO);
	ft_putnbr_fd(tokens->size, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	ft_putendl_fd("-------------------------", STDOUT_FILENO);
	
	current = tokens->head;
	i = 0;
	while (current)
	{
		ft_putstr_fd("Token [", STDOUT_FILENO);
		ft_putnbr_fd(i++, STDOUT_FILENO);
		ft_putstr_fd("] Type: ", STDOUT_FILENO);
		ft_putstr_fd((char *)get_token_type_str(current->type), STDOUT_FILENO);
		ft_putstr_fd("\n  Value: \"", STDOUT_FILENO);
		ft_putstr_fd(current->value, STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		ft_putendl_fd("-------------------------", STDOUT_FILENO);
		current = current->next;
	}
	ft_putchar_fd('\n', STDOUT_FILENO);
}

// Test cases for tokenizer
void	run_tokenizer_tests(void)
{
	char		*test_cases[] = {
		"echo hello world",
		"echo \"hello world\"",
		"echo 'hello world'",
		"ls -la | grep test",
		"cat < input.txt",
		"echo test > output.txt",
		"echo append >> file.txt",
		"cat << EOF",
		"echo $HOME",
		"echo \"My home is $HOME\"",
		"echo 'My home is $HOME'",
		"echo $USER | grep student",
		"echo Hello$USER",
		"ls | grep .c | wc -l",
		"\"echo\" 'hello' | cat",
		"echo $?",
		"echo \"$USER's home: $HOME\"",
		"echo $ | cat",
		"< infile grep \"test\" | sort > outfile",
		NULL
	};
	t_token_list	*tokens;
	int				i;

	ft_putendl_fd("\n=== RUNNING TOKENIZER TESTS ===\n", STDOUT_FILENO);
	i = 0;
	while (test_cases[i])
	{
		ft_putstr_fd("\nTest Case [", STDOUT_FILENO);
		ft_putnbr_fd(i + 1, STDOUT_FILENO);
		ft_putstr_fd("]: \"", STDOUT_FILENO);
		ft_putstr_fd(test_cases[i], STDOUT_FILENO);
		ft_putendl_fd("\"", STDOUT_FILENO);
		
		tokens = tokenizer(test_cases[i]);
		if (tokens)
			print_tokenizer_results(tokens);
		else
			ft_putendl_fd("ERROR: Tokenization failed!", STDOUT_FILENO);
		
		i++;
	}
	ft_putendl_fd("\n=== TOKENIZER TESTS COMPLETE ===\n", STDOUT_FILENO);
}
