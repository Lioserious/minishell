/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:43:20 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/26 17:10:19 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_cmd_node *node, t_env_list *env_list)
{
	if (!node->cmd || !node->cmd[0])
	{
		env_list->last_exitcode = 0;
		return ;
	}
	if (ft_strcmp(node->cmd[0], "pwd") == 0)
		ft_pwd(env_list);
	else if (ft_strcmp(node->cmd[0], "echo") == 0)
		ft_echo(node, env_list);
	else if (ft_strcmp(node->cmd[0], "cd") == 0)
		ft_cd(node, env_list);
	else if (ft_strcmp(node->cmd[0], "env") == 0)
		ft_env(env_list);
	else if (ft_strcmp(node->cmd[0], "export") == 0)
		ft_export(env_list, node);
	else if (ft_strcmp(node->cmd[0], "unset") == 0)
		ft_unset(env_list, node);
}
