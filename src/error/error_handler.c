/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:40 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 16:19:53 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_handler(char *message, int status)
{
	ft_putstr_fd("Error: ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
	exit(status);
}
