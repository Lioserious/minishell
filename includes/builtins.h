/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:57:06 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/05 15:28:26 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

int		ft_pwd(void);
int		ft_echo(t_cmd_node *node);
int		ft_cd(t_cmd_node *node, t_env_list *env_list);
int		ft_env(t_env_list *env_list);
int		ft_export(t_env_list *env_list, t_cmd_node *node);
void	ft_exit(t_cmd_node *node, t_env_list *env_list);
int		ft_unset(t_env_list *env_list, t_cmd_node *node);
#endif
