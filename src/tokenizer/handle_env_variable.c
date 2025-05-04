/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:42:04 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 17:23:23 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Environment-Variablen in Unix/Linux folgende Regeln haben:
// Sie dürfen Buchstaben (a-z, A-Z) enthalten
// Sie dürfen Ziffern (0-9) enthalten
// Sie dürfen Underscores (_) enthalten
// Sie müssen mit einem Buchstaben oder Underscore beginnen
//(nicht mit einer Ziffer)

int	handle_env_var(char *input, int *i, t_token_list *token_list)
{
	t_token	*new_token;
	int		start;
	int		len;
	char	*value;

	if (input[*i] != '$')
		return (0);
	start = (*i)++;
	if (input[*i] == '?')
	{
		(*i)++;
		new_token = create_token(TOKEN_ENV_VAR, "$?");
		return (add_token_to_list(token_list, new_token), 1);
	}
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	len = *i - start;
	if (len == 1)
	{
		new_token = create_token(TOKEN_WORD, "$");
		return (add_token_to_list(token_list, new_token), 1);
	}
	value = gc_substr(input, start, len);
	new_token = create_token(TOKEN_ENV_VAR, value);
	return (add_token_to_list(token_list, new_token), 1);
}
