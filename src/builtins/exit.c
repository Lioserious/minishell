/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:00:17 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/06 13:03:07 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_cmd_node *node)
{
	int	status;

	status = 0;
	if (node->cmd[1])
		status = ft_atoi(node->cmd[1]);
	garbage_collector_empty();
	rl_clear_history();
	exit(status);
}
