/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:23:02 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/26 09:58:24 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef	SIGNALS_H
# define SIGNALS_H
# include "minishell.h"

typedef struct	s_term {
	struct	termios	original;
}	t_term;

void	signal_setup();
void	terminal_setup(t_term *term);
void	heredoc_signal_handler(int sig);
void	restore_signals(void);

#endif
