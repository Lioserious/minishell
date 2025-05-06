/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:50:45 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/06 12:41:15 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
#define EXECUTION_H

#include "minishell.h"
#include <stdbool.h>
typedef	struct s_env_node
{
	char	*name;
	char	*value;
	bool	is_export;
	struct s_env_node	*next;
}	t_env_node;

typedef	struct s_env_list
{
	t_env_node	*head;
	int			count;
}	t_env_list;

t_env_list	*init_env_list(void);
int		ft_unset(t_env_list *env_list, t_cmd_node *node);
void	ft_add_env_var(t_env_list *env_list, char *name, char *value, int is_export);
int		ft_export(t_env_list *env_list, t_cmd_node *node);
int		ft_env(t_env_list *env_list);
void	init_env(t_env_list *env_list);
void	test_execute(t_cmd_node *node, t_env_list *env_list);
void	execute_builtin(t_cmd_node *node, t_env_list *env_list);
int		ft_pwd(void);
int		ft_echo(t_cmd_node *node);
int		ft_cd(t_cmd_node *node);
#endif
