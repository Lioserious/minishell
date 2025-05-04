/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:55 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/04 19:15:27 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "cmd_types.h"
# include "error.h"
# include "garbage_collector.h"
# include "libft.h"
# include "structs.h"
# include "execution.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

//readline
#include <readline/readline.h>
#include <readline/history.h>
#define PROMPT "miniarsch> "

#endif
