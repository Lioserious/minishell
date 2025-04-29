/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 09:37:28 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/15 16:15:51 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
			result[x] = (char *)malloc(sizeof(char) * (i - start + 2));
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
char	**ft_split(const char *s, char c)
{
	size_t	count;
	char	**result;

	if (s == NULL)
		return (NULL);
	count = count_sub(s, c);
	result = (char **)malloc(sizeof(char *) * (count + 1));
	if (!result)
		return (NULL);
	if (!fill_substrings(result, s, c))
	{
		free(result);
		return (NULL);
	}
	return (result);
}
