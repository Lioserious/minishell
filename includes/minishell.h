/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:01:55 by lihrig            #+#    #+#             */

/*   Updated: 2025/05/12 16:10:28 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
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

# define PROMPT "miniarsch> "
#endif
