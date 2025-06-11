/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:39:29 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/11 18:49:30 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipeline(t_env_list *env_list, t_cmd_node *node, pid_t *pids)
{
	int		i;
	t_exec	context;

	backup_std_fds(env_list);
	if (setup_all_heredocs(env_list, node))
	{
		cleanup_heredocs(node);
		_fds(env_list);
		return (0);
	}
	context.prev_fd = -1;
	context.i = 0;
	context.pids = pids;
	i = execute_pipeline_loop(node, env_list, &context);
	restore_std_fds(env_list);
	return (i);
}
