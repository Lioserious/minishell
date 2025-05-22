/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:11:31 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/22 16:09:28 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static char	*get_cmd_path(t_env_list *env_list, char *cmd);
static void	handle_child_process(t_cmd_node *node,
				t_env_list *env_list, char **enva);

void	execute_external(t_cmd_node *node, t_env_list *env_list)
{
	char	**enva;
	pid_t	pid;
	int		status;

	enva = convert_env_struct_array(env_list);
	pid = fork();
	if (pid == 0)
	{
		handle_child_process(node, env_list, enva);
	}
	else if (pid > 0)
		waitpid(pid, &status, 0);
	else
		perror("fork");
}

static char	*get_cmd_path(t_env_list *env_list, char *cmd)
{
	char	**path;
	char	*part_path;
	char	*full_path;
	int		i;

	path = gc_split(get_env_value(env_list, "PATH"), ':');
	i = 0;
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

static void	handle_child_process(t_cmd_node *node,
				t_env_list *env_list, char **enva)
{
	char	*cmd_path;

	cmd_path = get_cmd_path(env_list, node->cmd[0]);
	if (!cmd_path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(node->cmd[0], 2);
		ft_putendl_fd(": command not found", 2);
		clean_exit(1);
	}
	else
	{
		if (execve(cmd_path, node->cmd, enva) == -1)
		{
			perror("execve");
			clean_exit(1);
		}
	}
}
