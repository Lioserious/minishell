/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:26 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/06 13:56:20 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

# include "env.h"

void    clean_exit_old(int status);
void    *error_handler(char *message, int status);
void	*error_handler_exit_code(char *message, int exit_code,
		t_env_list *env_list);
void	*error_handler_env(char *message, t_env_list *env_list);
void	clean_exit(t_env_list *env_list);
void	update_exit_status(t_env_list *env_list, int status);

#endif
