/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:55 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/03 13:40:35 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "cmd_types.h"
# include "tokenizer.h"
# include "error.h"
# include "garbage_collector.h"
# include "libft.h"
# include "structs.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
//readline
#include <readline/readline.h>
#include <readline/history.h>
#define PROMPT "miniarsch> "

#endif
