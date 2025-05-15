/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 17:00:36 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/15 20:43:17 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENV_H
# define ENV_H

# include <stdbool.h>
// ========== ENV - STRUCTS ==========
typedef struct s_env_node
{
	char				*name;
	char				*value;
	bool				is_export;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_env_list
{
	t_env_node	*head;
	int			count;
}	t_env_list;

// ========== Functions ==========
t_env_list	*init_env_list(void);
void		init_env(t_env_list *env_list, char **env);
// ========== Helper Functions ==========
char		*get_env_value(t_env_list *env_list, char *name);
void		ft_add_env_var(t_env_list *env_list, char *name,
				char *value, int is_export);
void		set_env_var(t_env_list *env_list, char *name, char *value);
char		**convert_env_struct_array(t_env_list *env_list);
#endif
