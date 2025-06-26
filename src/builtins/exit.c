/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 13:00:17 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/26 16:32:45 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *str);

void	ft_exit(t_cmd_node *node, t_env_list *env_list,
			int stdin_b, int stdout_b)
{
	if (node->cmd[1] != NULL && node->cmd[2] != NULL)
	{
		ft_putendl_fd("minishell: exit: too many arguments", 2);
		env_list->last_exitcode = 1;
		return ;
	}
	if (node->cmd[1])
	{
		if (!is_numeric(node->cmd[1]))
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(node->cmd[1], 2);
			ft_putendl_fd(": numeric argument required", 2);
			env_list->last_exitcode = 255;
			close(stdin_b);
			close(stdout_b);
			clean_exit(env_list);
		}
		env_list->last_exitcode = ft_atoi(node->cmd[1]);
	}
	close(stdin_b);
	close(stdout_b);
	clean_exit(env_list);
}

static int	is_numeric(const char *str)
{
	int	i;

	i = 0;
	if (!str || !str[0])
		return (0);
	if (str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}
