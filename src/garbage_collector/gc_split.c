/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gc_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:15:30 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/08 16:16:09 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_sub(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c && i > 0 && s[i - 1] != c)
			count++;
		i++;
	}
	if (i > 0 && s[i - 1] != c)
		count++;
	return (count);
}

static int	fill_substrings(char **result, const char *s, char c)
{
	size_t	i;
	size_t	x;
	size_t	start;

	i = 0;
	x = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			start = i;
		if ((s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')))
		{
			result[x] = (char *)gc_malloc(sizeof(char) * (i - start + 2));
			if (!result[x])
			{
				while (x > 0)
					free(result[--x]);
				return (0);
			}
			ft_strlcpy(result[x++], &s[start], i - start + 2);
		}
		i++;
	}
	result[x] = NULL;
	return (1);
}

// Main split function
/**
 * @brief Teilt einen String an einem bestimmten Trennzeichen in Teilstrings
 *
 * Diese Funktion teilt den String 's' in Teilstrings, wobei das Zeichen 'c'
 * als Trennzeichen dient. Die Funktion gibt ein Array von Strings zurück,
 * wobei jeder String einem Teilstring entspricht. Das Array endet mit einem

	* NULL-Zeiger. Aufeinanderfolgende Trennzeichen werden als ein einziges
	* Trennzeichen
 * behandelt. Falls 's' NULL ist,
	wird NULL zurückgegeben. Bei einem Speicherfehler
 * während der Verarbeitung wird ebenfalls NULL zurückgegeben und der bereits
 * allozierte Speicher freigegeben.
 *
 * @param s Der zu teilende String
 * @param c Das Trennzeichen
 * @return Ein Array von Strings (Teilstrings) oder NULL bei Fehlern
 */
char	**ft_split(const char *s, char c)
{
	size_t	count;
	char	**result;

	if (s == NULL)
		return (NULL);
	count = count_sub(s, c);
	result = (char **)gc_malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	if (!fill_substrings(result, s, c))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
