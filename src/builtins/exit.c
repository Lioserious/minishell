/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:00:17 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/05 15:27:37 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_cmd_node *node, t_env_list *env_list)
{
	if (node->cmd[1])
		env_list->last_exitcode = ft_atoi(node->cmd[1]);
	clean_exit(env_list);
}
