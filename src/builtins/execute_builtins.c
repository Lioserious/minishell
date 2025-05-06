/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtins.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:43:20 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/06 13:05:34 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtin(t_cmd_node *node, t_env_list *env_list)
{
	if (ft_strncmp(node->cmd[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(node->cmd[0], "echo", 5) == 0)
		ft_echo(node);
	else if (ft_strncmp(node->cmd[0], "cd", 3) == 0)
		ft_cd(node);
	else if (ft_strncmp(node->cmd[0], "env", 4) == 0)
		ft_env(env_list);
	else if (ft_strncmp(node->cmd[0], "export", 7) == 0)
		ft_export(env_list, node);
	else if (ft_strncmp(node->cmd[0], "unset", 6) == 0)
		ft_unset(env_list, node);
	else if (ft_strncmp(node->cmd[0], "exit", 5) == 0)
		ft_exit(node);
}
