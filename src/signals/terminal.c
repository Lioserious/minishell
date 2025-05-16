/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 15:11:53 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/16 15:23:59 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

struct termios	terminal;

void	terminal_setup()
{
	tcgetattr(STDIN_FILENO, &terminal);
	terminal.c_lflag &= ~ECHOCTL;
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}

void	terminal_restore()
{
	tcsetattr(STDIN_FILENO, TCSANOW, &terminal);
}
