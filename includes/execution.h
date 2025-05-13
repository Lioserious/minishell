/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:50:45 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/13 10:58:36 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include "env.h"
# include <stdbool.h>

void	execute(t_env_list *env_list, t_cmd_node *node);
void	execute_builtin(t_cmd_node *node, t_env_list *env_list);
void	execute_external(t_cmd_node *node, t_env_list *env_list);
void	execute_redirections(t_file_list *file_list);
#endif
