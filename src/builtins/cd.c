/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:16:09 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/05 13:38:22 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(t_cmd_node *node)
{
	char	*home;

	if (!node->cmd[1])
	{
		home = getenv("HOME");
		if (home == NULL || chdir(home) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	if (chdir(node->cmd[1]) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(node->cmd[1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	return (0);
}


