/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:11:31 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/08 16:25:00 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void execute_external(node, env_list)
{

}

char	*get_cmd_path(t_env_list *env_list, char *cmd)
{
	char	**path;
	char	*part_path;
	char	*full_path;
	int		i;

	path = gc_split(get_env_value(env_list, "PATH"), ':');
	while (path[i])
	{
		part_path = gc_strjoin(path[i], "/");
		full_path = gc_strjoin(part_path, cmd);
		if (access(full_path, X_OK) == 0)
			return (full_path);
		i++;
	}
	return (NULL);
}
