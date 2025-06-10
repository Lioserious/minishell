/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:29:40 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/10 12:26:13 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*error_handler_env(char *message, t_env_list *env_list)
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

void	*error_handler(char *message, int status)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (status > 0)
		clean_exit_old(status);
	return (NULL);
}

void	*error_handler_exit_code(char *message, int exit_code,
		t_env_list *env_list)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	if (env_list)
		env_list->last_exitcode = exit_code;
	return (NULL);
}
