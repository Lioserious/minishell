/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:16:09 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/06 14:05:42 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_to_home(t_env_list *env_list);
static int	cd_to_oldpath(t_env_list *env_list);
static int	cd_to_path(char *path, t_env_list	*env_list);

void	ft_cd(t_cmd_node *node, t_env_list *env_list)
{
	if (!node->cmd[1] || node->cmd[1][0] == '~')
	{
		env_list->last_exitcode = cd_to_home(env_list);
	}
	if (node->cmd[1][0] == '-')
	{
		env_list->last_exitcode =cd_to_oldpath(env_list);
	}
	env_list->last_exitcode = cd_to_path(node->cmd[1], env_list);
}

static int	cd_to_home(t_env_list *env_list)
{
	char	*home;
	char	homepwd[PATH_MAX];
	char	oldpwd[PATH_MAX];

	home = getenv("HOME");
	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		return (1);
	if (home == NULL || chdir(home) != 0)
	{
		perror("cd");
		return (1);
	}
	set_env_var(env_list, "OLDPWD", gc_strdup(oldpwd));
	if (getcwd(homepwd, sizeof(homepwd)))
		set_env_var(env_list, "PWD", gc_strdup(home));
	return (0);
}

static int	cd_to_oldpath(t_env_list *env_list)
{
	char	*oldpwd;
	char	currentpwd[PATH_MAX];
	char	newpwd[PATH_MAX];

	oldpwd = get_env_value(env_list, "OLDPWD");
	if (oldpwd == NULL || chdir(oldpwd) != 0)
	{
		ft_putstr_fd("cd: OLDPWD not set or invalid\n", 2);
		return (1);
	}
	if (getcwd(currentpwd, sizeof(currentpwd)) == NULL)
		return (1);
	set_env_var(env_list, "OLDPWD", gc_strdup(oldpwd));
	ft_putstr_fd(oldpwd, 1);
	ft_putendl_fd("", 1);
	if (getcwd(newpwd, sizeof(newpwd)) == NULL)
		set_env_var(env_list, "PWD", gc_strdup(newpwd));
	return (0);
}

static int	cd_to_path(char *path, t_env_list	*env_list)
{
	char	oldpwd[PATH_MAX];
	char	cwd[PATH_MAX];

	if (getcwd(oldpwd, sizeof(oldpwd)) == NULL)
		return (1);
	if (chdir(path) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	set_env_var(env_list, "OLDPWD", gc_strdup(oldpwd));
	if (getcwd(cwd, sizeof(cwd)))
		set_env_var(env_list, "PWD", gc_strdup(cwd));
	return (0);
}
