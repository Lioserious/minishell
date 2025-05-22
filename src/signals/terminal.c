/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:11:53 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/19 15:46:03 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	terminal_setup(t_term *term)
{
	struct termios	current;

	if (tcgetattr(STDIN_FILENO, &term->original) == -1)
	{
		perror("tcgetattr");
		return;
	}
	current = term->original;
	current.c_lflag &= ~ECHOCTL;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &current) == -1)
		perror("tcsetattr");
}
