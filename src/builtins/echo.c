/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 11:16:33 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/19 16:02:23 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Prüft, ob ein Argument ein gültiges -n Flag ist
 * @param arg Das zu prüfende Argument
 * @return 1 wenn es ein gültiges -n Flag ist, sonst 0
 */
static int	is_n_flag(char *arg)
{
	int	j;

	j = 1;
	if (!arg || arg[0] != '-')
		return (0);
	if (arg[1] != 'n')
		return (0);
	while (arg[j] == 'n')
		j++;
	return (arg[j] == '\0');
}

/**
 * @brief Echo Builtin-Implementierung
 * @param node Command-Node mit Argumenten
 * @return Immer 0 für erfolgreiche Ausführung
 */
int	ft_echo(t_cmd_node *node)
{
	int	i;
	int	newline;

	i = 1;
	newline = 1;
	while (node->cmd[i] && is_n_flag(node->cmd[i]))
	{
		newline = 0;
		i++;
	}
	while (node->cmd[i])
	{
		ft_putstr_fd(node->cmd[i], 1);
		if (node->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		write(1, "\n", 1);
	return (0);
}
