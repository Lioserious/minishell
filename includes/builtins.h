/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:57:06 by mimalek           #+#    #+#             */
/*   Updated: 2025/06/26 15:41:40 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	ft_pwd(t_env_list *env_list);
void	ft_echo(t_cmd_node *node, t_env_list *env_list);
void	ft_cd(t_cmd_node *node, t_env_list *env_list);
void	ft_env(t_env_list *env_list);
void	ft_export(t_env_list *env_list, t_cmd_node *node);
void	ft_exit(t_cmd_node *node, t_env_list *env_list, int stdin_b, int stdout_b);
int		print_export_list(t_env_list	*env_list);
void	ft_unset(t_env_list *env_list, t_cmd_node *node);
#endif
