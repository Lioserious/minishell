/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:04:55 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/10 12:23:47 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Diese Funktion wird später implementiert
// Hier nur ein Platzhalter, um Kompilierungsfehler zu vermeiden
t_token	*parse_simple_command(t_token *token, t_cmd_list *cmd_list)
{
	t_cmd_node	*cmd;
	char		**cmd_array;
	int			arg_count;
	int			cmd_type;

	cmd_array = NULL;
	arg_count = 0;
	while (token && (token->type == TOKEN_WORD || token->type == TOKEN_ENV_VAR)
		&& !is_redirection_token(token->type) && token->type != TOKEN_PIPE
		&& token->type != TOKEN_EOF)
	{
		cmd_array = realloc_cmd_args(cmd_array, arg_count + 1);
		cmd_array[arg_count] = gc_strdup(token->value);
		arg_count++;
		token = token->next;
	}
	if (arg_count > 0)
	{
		cmd_type = is_builtin_command(cmd_array[0]);
		cmd = create_cmd_node(cmd_array, cmd_type);
		token = parse_redirections(token, cmd);
		add_cmd_to_list(cmd_list, cmd);
	}
	return (token);
}

/**
 * @brief Validates token list and handles edge cases
 * @param token_list Token list to validate
 * @param env_list Environment list for error handling
 * @return 1 if valid, 0 if invalid
 */
static int	validate_and_check_edge_cases(t_token_list *token_list,
		t_env_list *env_list)
{
	if (!token_list || !token_list->head)
		return (0);
	if (!validate_token_sequence(token_list, env_list))
		return (0);
	return (1);
}

/**
 * @brief Checks if token list contains only EOF token (empty command)
 * @param token_list Token list to check
 * @return 1 if only EOF, 0 otherwise
 */
static int	is_empty_command(t_token_list *token_list)
{
	return (token_list->size == 1 && token_list->head->type == TOKEN_EOF);
}

/**
 * @brief Processes the main parsing loop for commands and pipes
 * @param cmd_list Command list to populate
 * @param current_token Starting token
 * @return Final token position or NULL
 */
static t_token	*process_command_sequence(t_cmd_list *cmd_list,
		t_token *current_token)
{
	while (current_token && current_token->type != TOKEN_EOF)
	{
		if (!current_token->value || current_token->value[0] == '\0')
		{
			current_token = current_token->next;
			continue ;
		}
		current_token = parse_simple_command(current_token, cmd_list);
		if (!current_token)
			return (NULL);
		if (current_token->type == TOKEN_PIPE)
		{
			current_token = current_token->next;
			if (!current_token || current_token->type == TOKEN_EOF)
				break ;
		}
	}
	return (current_token);
}

/**
 * @brief Main parser function that coordinates the parsing process
 * @param token_list List of tokens to parse
 * @param env_list Environment variables
 * @return Parsed command list or NULL on error
 */
t_cmd_list	*parser(t_token_list *token_list, t_env_list *env_list)
{
	t_cmd_list	*cmd_list;
	t_token		*current_token;

	if (!validate_and_check_edge_cases(token_list, env_list))
		return (NULL);
	if (is_empty_command(token_list))
		return (create_cmd_list());
	cmd_list = create_cmd_list();
	current_token = token_list->head;
	process_command_sequence(cmd_list, current_token);
	return (cmd_list);
}
