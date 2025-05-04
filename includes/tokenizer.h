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

#endif