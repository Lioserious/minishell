/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:06:50 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/22 18:24:41 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Validiert Input-Parameter für Heredoc Expansion
 * @param line Input-Zeile
 * @param env_list Environment Variable Liste
 * @return Kopie der Zeile oder leerer String bei NULL
 */
static char	*validate_heredoc_input(char *line, t_env_list *env_list)
{
	if (!line || !env_list)
	{
		if (line)
			return (gc_strdup(line));
		else
			return (gc_strdup(""));
	}
	return (NULL);
}

/**
 * @brief Verarbeitet eine Environment Variable im Heredoc
 * @param line Input-Zeile
 * @param i Pointer auf aktuelle Position (wird aktualisiert)
 * @param env_list Environment Variable Liste
 * @param result Pointer auf Ergebnis-String
 */
static void	process_heredoc_variable(char *line, int *i, t_env_list *env_list, char **result)
{
	char	*part;

	part = process_env_var(line, i, env_list);
	add_to_word(result, part);
}

/**
 * @brief Verarbeitet normalen Text im Heredoc (zwischen Variablen)
 * @param line Input-Zeile
 * @param i Pointer auf aktuelle Position (wird aktualisiert)
 * @param result Pointer auf Ergebnis-String
 */
static void	process_heredoc_text(char *line, int *i, char **result)
{
	char	*part;
	int		start;

	start = *i;
	while (line[*i] && line[*i] != '$')
		(*i)++;
	part = gc_substr(line, start, *i - start);
	add_to_word(result, part);
}

/**
 * @brief Finalisiert das Ergebnis der Heredoc Expansion
 * @param result Aufgebauter Ergebnis-String
 * @return Finaler String oder leerer String bei NULL
 */
static char	*finalize_heredoc_result(char *result)
{
	if (result)
		return (result);
	else
		return (gc_strdup(""));
}

/**
 * @brief Expandiert Environment Variables in einer Heredoc-Zeile
 * @param line Die zu verarbeitende Zeile
 * @param env_list Environment Variable Liste
 * @return Neue Zeile mit expandierten Variablen
 */
char	*expand_heredoc_line(char *line, t_env_list *env_list)
{
	char	*result;
	char	*validation_result;
	int		i;

	validation_result = validate_heredoc_input(line, env_list);
	if (validation_result)
		return (validation_result);
	result = NULL;
	i = 0;
	while (line[i])
	{
		if (line[i] == '$')
			process_heredoc_variable(line, &i, env_list, &result);
		else
			process_heredoc_text(line, &i, &result);
	}
	return (finalize_heredoc_result(result));
}
