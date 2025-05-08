/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 12:58:09 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/08 13:04:57 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int is_redirection_token(t_token_type type)
{
    return (type == TOKEN_REDIR_OUT || type == TOKEN_REDIR_IN || 
            type == TOKEN_REDIR_APPEND || type == TOKEN_REDIR_HEREDOC);
}
