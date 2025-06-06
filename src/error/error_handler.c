/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:40 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/06 13:42:03 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*error_handler(char *message, t_env_list *env_list)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	restore_std_fds(env_list);
	garbage_collector_empty();
	rl_clear_history();
	env_list->last_exitcode = 1;
	exit(1);
	return (NULL);
}
