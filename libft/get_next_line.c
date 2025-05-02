/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:18:12 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:18:12 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*init_line(char **remainder)
{
	char	*line;

	if (*remainder && **remainder)
	{
		line = *remainder;
		*remainder = NULL;
	}
	else
	{
		free(*remainder);
		*remainder = NULL;
		line = malloc(1);
		if (!line)
			return (NULL);
		line[0] = '\0';
	}
	return (line);
}

static char	*read_from_file(int fd, char *line)
{
	char	buffer[BUFFER_SIZE + 1];
	char	*placeholder;
	int		b_read;

	while (!ft_strchr(line, '\n'))
	{
		b_read = read(fd, buffer, BUFFER_SIZE);
		if (b_read <= 0)
			break ;
		buffer[b_read] = '\0';
		placeholder = ft_strjoin(line, buffer);
		free(line);
		if (!placeholder)
			return (NULL);
		line = placeholder;
	}
	if (b_read < 0)
	{
		free(line);
		return (NULL);
	}
	return (line);
}

static char	*cut_newline(char **line, char **remainder)
{
	char	*new_pos;
	char	*final;

	new_pos = ft_strchr(*line, '\n');
	if (new_pos)
	{
		new_pos++;
		free(*remainder);
		*remainder = ft_strdup(new_pos);
		if (!*remainder)
		{
			free(*line);
			return (NULL);
		}
		*new_pos = '\0';
		final = ft_strdup(*line);
		free(*line);
		*line = NULL;
		return (final);
	}
	final = *line;
	*line = NULL;
	return (final);
}
/**
* @brief Liest eine Zeile aus einem File Descriptor
*
* Diese Funktion liest Daten aus dem übergebenen File Descriptor 'fd' und gibt
* die nächste Zeile zurück, die durch einen Zeilenumbruch oder das Dateiende
* begrenzt wird. Die Funktion verwendet einen statischen Puffer ('remainder'),
* um überschüssige gelesene Daten zwischen aufeinanderfolgenden Aufrufen zu
* speichern. Dadurch kann sie effizient mehrere Zeilen aus derselben Datei lesen.
*
* @param fd Der File Descriptor, aus dem gelesen werden soll
* @return Ein neu allozierter String, der die gelesene Zeile enthält
*			(mit Zeilenumbruch, falls vorhanden),oder NULL bei einem Fehler,
*			ungültigem File Descriptor, leerem Ergebnis oder Dateiende
*/

char	*get_next_line(int fd)
{
	static char	*remainder = NULL;
	char		*line;
	char		*result;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = init_line(&remainder);
	if (!line)
		return (NULL);
	line = read_from_file(fd, line);
	if (!line || *line == '\0')
	{
		free(remainder);
		remainder = NULL;
		free(line);
		return (NULL);
	}
	result = cut_newline(&line, &remainder);
	if (!result && remainder)
	{
		free(remainder);
		remainder = NULL;
	}
	return (result);
}
