/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:04:55 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/08 14:18:06 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token *parse_command(t_token *current, t_cmd_list *cmd_list)
{
	t_cmd_node *cmd_node;
	char **cmd_args;
	int arg_count;
	
	cmd_node = NULL;
	cmd_args = NULL;
	arg_count = 0;
	
	while(current && current->type != TOKEN_PIPE && current->type != TOKEN_EOF)
	{
		if(current->type == TOKEN_WORD || current->type == TOKEN_ENV_VAR)
			current = parse_command_word(current, &cmd_args, &arg_count);
		else if(is_redirection_token(current->type))
			current = parse_redirection(current, &cmd_node, &cmd_args, &arg_count);
		else
		{
			error_handler("SYNTAX ERROR: UNEXPECTED TOKEN", STDOUT_FILENO);
			
		}
	}
		finalize_command(&cmd_node, &cmd_args, arg_count);
		add_cmd_to_list(cmd_list, cmd_node);
		return (current);
}
t_token *parse_command_word(t_token *current, char ***cmd_args, int *arg_count)
{
    (*arg_count)++;
    *cmd_args = realloc_cmd_args(*cmd_args, *arg_count);
    
    if (current->type == TOKEN_ENV_VAR)
        (*cmd_args)[*arg_count - 1] = expand_env_var(current->value);
    else
        (*cmd_args)[*arg_count - 1] = gc_strdup(current->value);
    return (current->next);
}
t_cmd_list *parser(t_token_list *token_list)
{
    t_cmd_list *cmd_list;
    t_token *current;
    
    if (!token_list || !token_list->head)
        return (NULL);
    cmd_list = create_cmd_list();
    if (!cmd_list)
        return (NULL);
    current = token_list->head;
	while (current && current->type != TOKEN_EOF)
	{
		current = parse_command(current, cmd_list);
		if (current && current->type == TOKEN_PIPE)
			current = current->next;
	}
	return (cmd_list);
}
