#ifndef TOKENIZER_H
# define TOKENIZER_H

typedef enum e_token_type
{
    TOKEN_WORD,         // Normale Wörter
    TOKEN_PIPE,         // |
    TOKEN_REDIR_IN,     // 
    TOKEN_REDIR_OUT,    // >
    TOKEN_REDIR_APPEND, // >>
    TOKEN_REDIR_HEREDOC,// 
	TOKEN_ENV_VAR,		// $ENV
    TOKEN_EOF           // Ende des Inputs
} t_token_type;

typedef struct s_token_list
{
    t_token     *head;
    t_token     *tail;
    ssize_t     size;
}               t_token_list;

typedef struct s_token
{
    t_token_type    type;
    char            *value;
    struct s_token  *next;
}                   t_token;

t_token_list *create_token_list(void);
t_token *create_token(t_token_type type, char *value);
void add_token_to_list (t_token_list *list, t_token *token);

int is_whitespace(char c);
int is_special_char(char c);
int	is_quote(char c);
int	is_env_var(char c);

char *extract_word(char *input, int *i);
int	handle_special_char(char *input, int *i, t_token_list *token_list);
int	handle_env_var(char *input, int *i, t_token_list *token_list);

int	handle_double_quote(char *input, int *i, t_token_list *token_list);
int	handle_single_quote(char *input, int *i, t_token_list *token_list);

t_token_list	*tokenizer(char *input);
#endif