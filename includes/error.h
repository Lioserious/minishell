/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:26 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/06 12:14:29 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	*error_handler(char *message, t_env_list *env_list);
void	clean_exit(t_env_list *env_list);
void	update_exit_status(t_env_list *env_list, int status);

#endif
