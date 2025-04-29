/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 15:55:07 by mimalek           #+#    #+#             */
/*   Updated: 2024/11/05 12:09:19 by mimalek          ###   ########.fr       */
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
