/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_exit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 10:35:26 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/06 11:48:02 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clean_exit(t_env_list *env_list)
{
	restore_std_fds(env_list);
	garbage_collector_empty();
	rl_clear_history();
	exit(env_list->last_exitcode);
}
