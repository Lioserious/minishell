/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 13:16:09 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/07 15:47:27 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_move_to_oldpwd(t_env_list *env_list);

int	ft_cd(t_cmd_node *node, t_env_list *env_list)
{
	char	*home;
	char	current_dir[PATH_MAX];
	char	cwd[PATH_MAX];

	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
		set_env_var(env_list, "OLDPWD", gc_strdup(current_dir));
	if (!node->cmd[1] || node->cmd[1][0] == '~')
	{
		home = getenv("HOME");
		if (home == NULL || chdir(home) != 0)
		{
			perror("cd");
			return (1);
		}
		set_env_var(env_list, "PWD", gc_strdup(home));
		return (0);
	}
	if (node->cmd[1][0] == '-')
	{
		ft_move_to_oldpwd(env_list);
		return (0);
	}
	if (chdir(node->cmd[1]) != 0)
	{
		ft_putstr_fd("cd: ", 2);
		ft_putstr_fd(node->cmd[1], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		return (1);
	}
	if (getcwd(cwd, sizeof(cwd)))
		set_env_var(env_list, "PWD", gc_strdup(cwd));
	return (0);
}

void	ft_move_to_oldpwd(t_env_list *env_list)
{
	char		*oldpwd;
	t_env_node	*current;

	current = env_list->head;
	while (ft_strncmp(current->name, "OLDPWD", 7) != 0)
		current = current->next;
	oldpwd = current->value;
	if (chdir(oldpwd) != 0)
	{
		perror("cd");
		return ;
	}
	ft_putstr_fd(oldpwd , 1);
	ft_putendl_fd("", 1);
	set_env_var(env_list, "PWD", gc_strdup(oldpwd));
	return ;
}
