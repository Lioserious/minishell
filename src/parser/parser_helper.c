/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:58:09 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/16 15:11:30 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_redirection_token(t_token_type type)
{
	return (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_IN
		|| type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}

// Argument-Array zu vergrößern.
char	**realloc_cmd_args(char **args, int new_size)
{
	char	**new_args;
	int		i;

	i = 0;
	new_args = (char **)gc_malloc(sizeof(char *) * (new_size + 1));
	if (!new_args)
		error_handler("MEMORY ALLOCATION FAILED: REALLOC_CMD_ARGS", 1);
	while (i < new_size - 1 && args && args[i])
	{
		new_args[i] = args[i];
		i++;
	}
	new_args[new_size] = NULL;
	return (new_args);
}

int is_builtin_command(char *cmd)
{
    if (!cmd)
        return (CMD_SIMPLE);
    
    if (ft_strcmp(cmd, "cd") == 0 ||
        ft_strcmp(cmd, "echo") == 0 ||
        ft_strcmp(cmd, "env") == 0 ||
        ft_strcmp(cmd, "export") == 0 ||
        ft_strcmp(cmd, "unset") == 0 ||
        ft_strcmp(cmd, "exit") == 0 ||
        ft_strcmp(cmd, "pwd") == 0)
        return (CMD_BUILTIN);
    
    return (CMD_SIMPLE);
}
