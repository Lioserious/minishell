/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 17:37:57 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/10 13:32:34 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_env_list *env_list)
{
	char	cwd[PATH_MAX];

	if (getcwd(cwd, PATH_MAX) != NULL)
	{
		//ft_putendl_fd(cwd, 1);
		env_list->last_exitcode = 0;
	}
	else
	{
		perror("pwd");
		env_list->last_exitcode = 1;
	}
}
