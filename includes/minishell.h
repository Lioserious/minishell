/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:27:21 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/15 21:34:52 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include "structs.h"
# include "cmd_types.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "env.h"
# include "tokenizer.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>
// readline
# include <readline/history.h>
# include <readline/readline.h>

// Standard-Bibliotheken
# include "error.h"
# include "garbage_collector.h"
# include "libft.h"

// Dann Strukturdefinitionen und Enums
# include "builtins.h"
# include "parser.h"
# include "execution.h"

# define PROMPT "miniarsch> "
#endif
