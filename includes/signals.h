/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:23:02 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/29 16:01:40 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H
# include "minishell.h"

typedef struct s_term
{
	struct termios	original;
}					t_term;

void				signal_setup(void);
void				main_sigint_handler(int sig);
void				terminal_setup(t_term *term);
void				heredoc_signal_handler(int sig);
void				restore_signals(void);

#endif
