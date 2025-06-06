/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 21:26:17 by lihrig            #+#    #+#             */
/*   Updated: 2025/06/05 14:58:34 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZER_H
# define TOKENIZER_H

# include "env.h"
# include <stddef.h>
/*
	TOKEN_WORD,          Normale Wörter
	TOKEN_PIPE,          |
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,      >
	TOKEN_REDIR_APPEND,   >>
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,       $ENV
	TOKEN_EOF            Ende des Inputs
*/
typedef enum e_token_type
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_ENV_VAR,
	TOKEN_EOF
}					t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*value;
	struct s_token	*next;
}					t_token;

typedef struct s_token_list
{
	t_token			*head;
	t_token			*tail;
	size_t			size;
}					t_token_list;
// Workaround fuer Norm
typedef struct s_quote_parser
{
	char			*input;
	int				*i_ptr;
	char			**result;
	int				*start_ptr;
	t_env_list		*env_list;
}					t_quote_parser;

//
char				*collect_quoted_delimiter(char *input, int *i,
						char quote_char);
char				*collect_unquoted_delimiter(char *input, int *i);
void				handle_heredoc_delimiter(char *input, int *i,
						t_token_list *token_list);
void				handle_heredoc(char *input, int *i,
						t_token_list *token_list);
void				handle_simple_input_redir(char *input, int *i,
						t_token_list *token_list);
t_token_list		*create_token_list(void);
t_token				*create_token(t_token_type type, char *value);
void				add_token_to_list(t_token_list *list, t_token *token);
int					handle_input_redirection(char *input, int *i,
						t_token_list *token_list);
void				add_eof_token(t_token_list *token_list);

t_token_list		*tokenizer(char *input, t_env_list *env_list);

int					is_heredoc_delimiter_quoted(char *delimiter);
int					is_quote(char c);
int					is_env_var(char c);
int					is_whitespace(char c);
int					handle_special_char(char *input, int *i,
						t_token_list *token_list);
char				*process_tilde(char *input, int *i, t_env_list *env_list);
// Neue Hilfsfunktionen für den Tokenizer
int					is_special_operator(char c);
void				add_to_word(char **word, char *part);
void				add_word_token(t_token_list *token_list, char *word);

// Funktionen für Umgebungsvariablen
char				*get_exit_status_as_string(t_env_list *env_list);
char				*process_env_var(char *input, int *i, t_env_list *env_list);

// Funktionen für Anführungszeichen
char				*process_single_quote(char *input, int *i);
char				*process_double_quote(char *input, int *i,
						t_env_list *env_list);

// Funktionen für Wortverarbeitung
char				*process_word_part(char *input, int *i);
void				process_word(char *input, int *i, t_token_list *token_list,
						t_env_list *env_list);
// Funktionen zur initalisierung des parsers
void				init_quote_parser_base(t_quote_parser *parser, char *input,
						int *i_ptr, char **result);
void				complete_quote_parser(t_quote_parser *parser,
						int *start_ptr, t_env_list *env_list);
#endif
