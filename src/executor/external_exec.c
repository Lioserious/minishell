/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   external_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/08 16:11:31 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/29 15:30:05 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_external_cmd(t_cmd_node *node, t_env_list *env_list,
				char **enva);
static void	exec_minishell(t_cmd_node *node, char **enva);

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

	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return (gc_strdup(cmd));
		return (NULL);
	}
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

void	handle_child_process(t_cmd_node *node, t_env_list *env_list,
		char **enva)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (ft_strcmp(node->cmd[0], "./minishell") == 0 || ft_strcmp(node->cmd[0],
			"minishell") == 0)
	{
		exec_minishell(node, enva);
	}
	else
		exec_external_cmd(node, env_list, enva);
}

static void	exec_external_cmd(t_cmd_node *node, t_env_list *env_list,
		char **enva)
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
	if (execve(cmd_path, node->cmd, enva) == -1)
	{
		perror("execve");
		clean_exit(1);
	}
}

static void	exec_minishell(t_cmd_node *node, char **enva)
{
	if (execve("./minishell", node->cmd, enva) == -1)
	{
		perror("execve");
		clean_exit(1);
	}
}
