/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nudel.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 17:45:24 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/16 17:55:08 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Expands tilde (~) to home directory
 * @param input Input string
 * @param i Current position pointer
 * @param env_list Environment variable list
 * @return Expanded home directory or "~" if not expandable
 */
char *process_tilde(char *input, int *i, t_env_list *env_list)
{
    if (input[*i] != '~')
        return (NULL);
    (*i)++;
    if (((*i) == 1 || is_whitespace(input[(*i) - 2]) || 
         is_special_operator(input[(*i) - 2])) && 
        (input[*i] == '/' || input[*i] == '\0' || 
         is_whitespace(input[*i]) || is_special_operator(input[*i])))
    {
        char *home_dir = get_env_value(env_list, "HOME");
        if (!home_dir || home_dir[0] == '\0')
            return (gc_strdup("~"));
        return (home_dir);
    }
    (*i)--;
    return (gc_strdup("~"));
}
