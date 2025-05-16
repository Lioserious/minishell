/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_eof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:14:19 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 17:23:25 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_eof_token(t_token_list *token_list)
{
	t_token	*eof_token;

	eof_token = create_token(TOKEN_EOF, "EOF");
	if (eof_token)
		add_token_to_list(token_list, eof_token);
}
