/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:55 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/12 15:47:40 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "cmd_types.h"
# include "error.h"
# include "garbage_collector.h"
# include "libft.h"
# include "parser.h"
# include "structs.h"
# include "tokenizer.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

// readline
# include <readline/history.h>
# include <readline/readline.h>
# define PROMPT "miniarsch> "

#endif
