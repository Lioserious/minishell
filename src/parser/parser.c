/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:04:55 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/08 12:42:07 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd_list *parser(t_token_list *token_list)
{
	t_cmd_list *cmd_list = create_cmd_list();
	t_token *current;
	
	t_token *current = token_list->head;
	while (current && current->type != TOKEN_EOF)
	{
		
	}
	return (cmd_list);
}