/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 18:34:04 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/26 09:02:34 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Initialisiert die Heredoc Pipe
 * @param heredoc_pipe Array für die Pipe File Descriptors
 * @return 0 bei Erfolg, -1 bei Fehler
 */
int	init_heredoc_pipe(int *heredoc_pipe)
{
	if (pipe(heredoc_pipe) == -1)
	{
		perror("pipe");
		clean_exit(1);
		return (-1);
	}
	return (0);
}

/**
 * @brief Prüft ob eine Zeile das Heredoc beenden soll
 * @param line Die eingegebene Zeile
 * @param delimiter Der Heredoc Delimiter
 * @return 1 wenn Heredoc beendet werden soll, 0 sonst
 */
int	should_end_heredoc(char *line, char *delimiter)
{
	if (!line)
		return (1);
	if (ft_strcmp(line, delimiter) == 0)
		return (1);
	return (0);
}

/**
 * @brief Verarbeitet und schreibt eine einzelne Heredoc-Zeile
 * @param line Die zu verarbeitende Zeile
 * @param file File-Node mit Expansion-Einstellungen
 * @param env_list Environment Variable Liste
 * @param pipe_fd Write-End der Pipe
 */
void	process_and_write_line(char *line, t_file_node *file,
								t_env_list *env_list, int pipe_fd)
{
	char	*processed_line;

	if (file->expand_vars)
	{
		processed_line = expand_heredoc_line(line, env_list);
		write(pipe_fd, processed_line, ft_strlen(processed_line));
	}
	else
	{
		write(pipe_fd, line, ft_strlen(line));
	}
	write(pipe_fd, "\n", 1);
}

void	finalize_heredoc_pipe(t_file_node *file, int *heredoc_pipe)
{
	close(heredoc_pipe[1]);
	file->heredoc_fd = heredoc_pipe[0];
}
