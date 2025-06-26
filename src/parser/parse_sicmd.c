/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sicmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:08:25 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/26 12:50:26 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialisiert die Environment-Daten der Parse-Struktur
 * @param parse_data Zu initialisierende Struktur
 * @param cmd_list Command list
 * @param env_list Environment list
 */
static void	init_parse_env_data(t_parse_cmd *parse_data, t_cmd_list *cmd_list,
		t_env_list *env_list)
{
	parse_data->cmd_list = cmd_list;
	parse_data->env_list = env_list;
}

/**
 * @brief Sammelt alle Wort-Tokens für einen Command
 * @param token Aktueller Token
 * @param cmd_array Pointer auf Command-Array
 * @param arg_count Pointer auf Argument-Zähler
 * @return Nächster Token nach allen Word-Tokens
 */
static t_token	*collect_command_arguments(t_token *token, char ***cmd_array,
		int *arg_count)
{
	*cmd_array = NULL;
	*arg_count = 0;
	while (token && (token->type == TOKEN_WORD || token->type == TOKEN_ENV_VAR)
		&& !is_redirection_token(token->type) && token->type != TOKEN_PIPE
		&& token->type != TOKEN_EOF)
	{
		*cmd_array = realloc_cmd_args(*cmd_array, *arg_count + 1);
		(*cmd_array)[*arg_count] = gc_strdup(token->value);
		(*arg_count)++;
		token = token->next;
	}
	return (token);
}

/**
 * @brief Prüft ob Redirections nach den Command-Argumenten folgen
 * @param token Aktueller Token
 * @return 1 wenn Redirections vorhanden, 0 sonst
 */
static int	has_pending_redirections(t_token *token)
{
	return (token && is_redirection_token(token->type));
}

/**
 * @brief Erstellt und konfiguriert einen Command-Node
 * @param cmd_array Array mit Command-Argumenten (kann NULL sein)
 * @param arg_count Anzahl der Argumente
 * @param token Aktueller Token für Redirections
 * @param cmd_list Command-Liste zum Hinzufügen
 * @param env_list Environment list for error handling
 * @return Nächster Token nach Verarbeitung
 */
static t_token	*create_and_configure_command(t_token *token,
		t_parse_cmd *parse_data)
{
	t_cmd_node	*cmd;
	int			cmd_type;

	if (parse_data->arg_count > 0)
		cmd_type = is_builtin_command(parse_data->cmd_array[0]);
	else
		cmd_type = CMD_SIMPLE;
	cmd = create_cmd_node(parse_data->cmd_array, cmd_type);
	if (!cmd)
		return (NULL);
	token = parse_redirections(token, cmd, parse_data->env_list);
	if (!token && has_pending_redirections(token))
		return (NULL);
	add_cmd_to_list(parse_data->cmd_list, cmd);
	return (token);
}

/**
 * @brief Hauptfunktion zum Parsen eines einfachen Commands
 * @param token Aktueller Token
 * @param cmd_list Command-Liste zum Hinzufügen
 * @param env_list Environment list for error handling
 * @return Nächster Token nach Verarbeitung oder NULL bei Fehler
 */
t_token	*parse_simple_command(t_token *token, t_cmd_list *cmd_list,
		t_env_list *env_list)
{
	char		**cmd_array;
	int			arg_count;
	int			has_redirections;
	t_parse_cmd	parse_data;

	token = collect_command_arguments(token, &cmd_array, &arg_count);
	has_redirections = has_pending_redirections(token);
	if (arg_count > 0 || has_redirections)
	{
		init_parse_cmd_data(&parse_data, cmd_array, arg_count);
		init_parse_env_data(&parse_data, cmd_list, env_list);
		token = create_and_configure_command(token, &parse_data);
		if (!token)
			return (NULL);
	}
	return (token);
}
