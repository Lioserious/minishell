/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:16:09 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/07 16:13:26 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		cd_to_home(t_env_list *env_list);
int		cd_to_oldpath(t_env_list *env_list);
int		cd_to_path(char *path, t_env_list	*env_list);

int	ft_cd(t_cmd_node *node, t_env_list *env_list)
{
	char	current_dir[PATH_MAX];

	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
		set_env_var(env_list, "OLDPWD", gc_strdup(current_dir));
	if (!node->cmd[1] || node->cmd[1][0] == '~')
	{
		return (cd_to_home(env_list));
	}
	if (node->cmd[1][0] == '-')
	{
		return (cd_to_oldpath(env_list));
	}
	return (cd_to_path(node->cmd[1], env_list));
}

int	cd_to_home(t_env_list *env_list)
{
	char	*home;

	home = getenv("HOME");
	if (home == NULL || chdir(home) != 0)
	{
		perror("cd");
		return (1);
	}
	set_env_var(env_list, "PWD", gc_strdup(home));
	return (0);
}

int	cd_to_oldpath(t_env_list *env_list)
{
	char	*oldpwd;

	oldpwd = get_env_value(env_list, "OLDPWD");
	if (oldpwd == NULL || chdir(oldpwd) != 0)
	{
		ft_putstr_fd("cd: OLDPWD not set or invalid\n", 2);
		return (1);
	}
	set_env_var(env_list, "OLDPWD", gc_strdup(oldpwd));
	ft_putstr_fd(oldpwd, 1);
	ft_putendl_fd("", 1);
	return (0);
}

int	cd_to_path(char *path, t_env_list	*env_list)
{
	char	cwd[PATH_MAX];

	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		set_env_var(env_list, "PWD", gc_strdup(cwd));
	return (0);
}
