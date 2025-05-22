/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_variable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 14:42:04 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/19 16:37:26 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "env.h"
#include "minishell.h"

/**
 * @brief Returns the last exit status as a string
 * @return String representation of the exit status
 */
char	*get_exit_status_as_string(void)
{
	int	exit_status;

	exit_status = 0;
	return (gc_strdup(ft_itoa(exit_status)));
}

/**
 * @brief Tests progressively shorter variable names
 * @param input Input string
 * @param i Current position pointer
 * @param name_start Start position of variable name
 * @param env_list Environment variable list
 * @return Variable value or "$" if not found
 */

// char	*try_shorter_var_names(char *input, int *i, int name_start,
// 		t_env_list *env_list)
// {
// 	char	*tested_var;
// 	char	*env_value;
// 	int		current_length;

// 	current_length = *i - name_start;
// 	while (current_length > 0)
// 	{
// 		current_length--;
// 		tested_var = gc_substr(input, name_start, current_length);
// 		if (!tested_var)
// 			return (gc_strdup("$"));
// 		env_value = get_env_value(env_list, tested_var);
// 		if (env_value && env_value[0] != '\0')
// 		{
// 			*i = name_start + current_length;
// 			return (env_value);
// 		}
// 	}
// 	*i = name_start;
// 	return (gc_strdup("$"));
// }

/**
 * @brief Processes environment variables in the input
 * @param input Input string
 * @param i Current position pointer
 * @param env_list Environment variable list
 * @return Value of the variable or "$" if not valid
 *
 * Handles:
 * - Valid variable names (letters, digits, underscores)
 * - Special case $? for exit status
 * - Progressive shortening for partial matches
 */
char	*process_env_var(char *input, int *i, t_env_list *env_list)
{
	char	*var_name;
	char	*env_value;
	int		name_start;

	if (!input || input[*i] != '$')
		return (NULL);
	(*i)++;
	if (!input[*i])
		return (gc_strdup("$"));
	if (input[*i] == '?')
		return ((*i)++, get_exit_status_as_string());
	name_start = *i;
	while (input[*i] && (ft_isalnum(input[*i]) || input[*i] == '_'))
		(*i)++;
	if (*i == name_start)
		return ((*i) = name_start, gc_strdup("$"));
	var_name = gc_substr(input, name_start, *i - name_start);
	if (!var_name)
		return (gc_strdup("$"));
	env_value = get_env_value(env_list, var_name);
	return (env_value);
}
