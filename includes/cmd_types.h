/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_types.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:00:59 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/12 12:31:47 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_TYPES_H
# define CMD_TYPES_H

typedef enum e_cmd_type
{
    CMD_SIMPLE = 1,     /* Ein einfacher Befehl (ls -la) */
    CMD_PIPE = 2,       /* Teil einer Pipeline (cmd | cmd) */
    CMD_BUILTIN = 3,    /* Eingebauter Befehl (cd, echo, etc.) */
}   t_cmd_type;

/* Redirection Types */
typedef enum e_redir_type
{
    REDIR_IN = 1,       /* Input Redirection (<) */
    REDIR_OUT = 2,      /* Output Redirection (>) */
    REDIR_APPEND = 3,   /* Append Output (>>) */
    REDIR_HEREDOC = 4   /* Here Document (<<) */
}   t_redir_type;

#endif