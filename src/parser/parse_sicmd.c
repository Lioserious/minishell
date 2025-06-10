/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sicmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/10 13:08:25 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/10 13:28:01 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
 * @return Nächster Token nach Verarbeitung
 */
static t_token	*create_and_configure_command(char **cmd_array, int arg_count,
		t_token *token, t_cmd_list *cmd_list)
{
	t_cmd_node	*cmd;
	int			cmd_type;

	if (arg_count > 0)
		cmd_type = is_builtin_command(cmd_array[0]);
	else
		cmd_type = CMD_SIMPLE; // Leere Commands sind keine Builtins
	cmd = create_cmd_node(cmd_array, cmd_type);
	if (!cmd)
		return (NULL);
	token = parse_redirections(token, cmd);
	if (!token && has_pending_redirections(token))
		return (NULL); // Fehler beim Parsen der Redirections
	add_cmd_to_list(cmd_list, cmd);
	return (token);
}

/**
 * @brief Hauptfunktion zum Parsen eines einfachen Commands
 * @param token Aktueller Token
 * @param cmd_list Command-Liste zum Hinzufügen
 * @return Nächster Token nach Verarbeitung oder NULL bei Fehler
 *
 * Diese Funktion verarbeitet:
 * - Commands mit Argumenten: "ls -la"
 * - Commands mit Redirections: "ls > file.txt"
 * - Nur Redirections: "> file.txt" (leerer Command)
 * - Kombinationen: "echo hello > file.txt"
 */
t_token	*parse_simple_command(t_token *token, t_cmd_list *cmd_list)
{
	char	**cmd_array;
	int		arg_count;
	int		has_redirections;

	// Schritt 1: Sammle alle Command-Argumente
	token = collect_command_arguments(token, &cmd_array, &arg_count);
	// Schritt 2: Prüfe ob Redirections folgen
	has_redirections = has_pending_redirections(token);
	// Schritt 3: Erstelle Command-Node wenn Argumente ODER Redirections vorhanden
	if (arg_count > 0 || has_redirections)
	{
		token = create_and_configure_command(cmd_array, arg_count, token,
				cmd_list);
	}
	return (token);
}
