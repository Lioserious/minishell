/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nudel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:45:24 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/22 14:17:35 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	should_expand_tilde(char *input, int i)
{
	int	preceded_by_delimiter;
	int	followed_by_delimiter;

	preceded_by_delimiter = (i == 0) || is_whitespace(input[i - 1])
		|| is_special_operator(input[i - 1]);
	followed_by_delimiter = (input[i + 1] == '\0') || (input[i + 1] == '/')
		|| is_whitespace(input[i + 1]) || is_special_operator(input[i + 1]);
	return (preceded_by_delimiter && followed_by_delimiter);
}

/**
 * @brief Expands tilde (~) to home directory
 * @param input Input string
 * @param i Current position pointer
 * @param env_list Environment variable list
 * @return Expanded home directory or "~" if not expandable
 */
char	*process_tilde(char *input, int *i, t_env_list *env_list)
{
	char	*home_dir;

	if (input[*i] != '~')
		return (NULL);
	if (!should_expand_tilde(input, *i))
	{
		(*i)++;
		return (gc_strdup("~"));
	}
	(*i)++;
	home_dir = get_env_value(env_list, "HOME");
	if (!home_dir || home_dir[0] == '\0')
		return (gc_strdup("~"));
	return (home_dir);
}
