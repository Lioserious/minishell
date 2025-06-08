/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 14:08:05 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/08 14:08:13 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	print_export_list(t_env_list	*env_list)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
	{
		if (current->is_export)
		{
			ft_putstr_fd("declare -x ", 1);
			ft_putstr_fd(current->name, 1);
			if (current->value)
			{
				ft_putchar_fd('=', 1);
				ft_putchar_fd('"', 1);
				ft_putstr_fd(current->value, 1);
				ft_putchar_fd('"', 1);
			}
			ft_putchar_fd('\n', 1);
		}
		current = current->next;
	}
	return (0);
}
