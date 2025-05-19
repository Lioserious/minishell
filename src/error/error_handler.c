/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:40 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/19 12:51:03 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Handles errors with optional termination
 * @param message Error message to display
 * @param status Error status code (0 = non-fatal, other = fatal)
 * @return void* NULL pointer for convenient use in functions
 */
void *error_handler(char *message, int status)
{
    ft_putstr_fd("minishell: ", STDERR_FILENO);
    ft_putstr_fd(message, STDERR_FILENO);
    ft_putstr_fd("\n", STDERR_FILENO);
    if (status > 0)
        clean_exit(status);
    return NULL;
}
