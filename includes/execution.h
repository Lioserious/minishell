/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/04 18:50:45 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/07 17:10:37 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"
# include <stdbool.h>

void	test_execute(t_cmd_node *node, t_env_list *env_list);
void	execute_builtin(t_cmd_node *node, t_env_list *env_list);

#endif
