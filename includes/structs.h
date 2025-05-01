#ifndef STRUCTS_H
# define STRUCTS_H

#include "minishell.h"
// Shortcuts //
typedef struct s_cmd_node t_cmd_node;
typedef	struct	s_file_list	t_file_list;
typedef	struct	s_file_node	t_file_node;

//command line struct
typedef struct	s_cmd_list
{
	t_cmd_node	*head;
	t_cmd_node	*tail;
	ssize_t		size;
}	t_cmd_list;

//command struct
typedef struct s_cmd_node
{
	int			cmd_type;
	char		**cmd;
	t_file_list	*file;
	t_cmd_node	*next;
} t_cmd_node;

//file list struct
typedef	struct	s_file_list
{
	t_file_node	*head;
	t_file_node	*tail;
	ssize_t		size;
}	t_file_list;

//file struct
typedef	struct	s_file_node
{
	char	*name;
	int		redirection_type;
	t_file_node	*next;
}	t_file_node;

//commands
t_cmd_list *create_cmd_list(void);
t_cmd_node	*create_cmd_node(char **cmd, int cmd_type);
//files
t_file_list *create_file_list(void);
t_file_node *create_file_node(char *name, int redirection_type);
void add_cmd_to_list(t_cmd_list *list, t_cmd_node *node);

#endif
