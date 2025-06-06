/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:35:26 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/06 13:56:06 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    clean_exit_old(int status)
{
    garbage_collector_empty();
    rl_clear_history();
    exit(status);
}

void	clean_exit(t_env_list *env_list)
{
	restore_std_fds(env_list);
	garbage_collector_empty();
	rl_clear_history();
	exit(env_list->last_exitcode);
}

void	update_exit_status(t_env_list *env_list, int status)
{
	int	sig;

	if (WIFEXITED(status))
		env_list->last_exitcode = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
	{
		sig = WTERMSIG(status);
		env_list->last_exitcode = 128 + sig;
	}
	else if (WIFSTOPPED(status))
		env_list->last_exitcode = 128 + WSTOPSIG(status);
	else
		env_list->last_exitcode = 1;
}
