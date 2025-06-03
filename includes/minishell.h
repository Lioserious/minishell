/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:27:21 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/03 20:13:00 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <errno.h>
# include <signal.h>
# include <termios.h>
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

# include "cmd_types.h"
# include "structs.h"

# include "signals.h"
# include "execution.h"
# include "builtins.h"
# include "env.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <termios.h>

# include "tokenizer.h"
# include "parser.h"
# include "execution.h"

extern volatile sig_atomic_t	g_heredoc;

# define PROMPT "miniarsch> "
#endif
