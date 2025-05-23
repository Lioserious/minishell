/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 12:11:42 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/23 15:17:43 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t g_heredoc = 0;

void	main_sigint_handler(int sig);

void	signal_setup(void)
{
	struct sigaction	sa;

	sa.sa_handler = main_sigint_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	main_sigint_handler(int sig)
{
	(void)sig;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	heredoc_signal_handler(int sig)
{
	(void)sig;
	g_heredoc = 1;
	//write(STDOUT_FILENO, "\n", 1);
	//rl_on_new_line();
	//rl_replace_line("", 0);
	//rl_done = 1;
	close(STDIN_FILENO);
}
