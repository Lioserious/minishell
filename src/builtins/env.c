/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:53:12 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/07 16:01:40 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_list	*init_env_list(void)
{
	t_env_list	*env_list;

	env_list = (t_env_list *)gc_malloc(sizeof(t_env_list));
	env_list->head = NULL;
	env_list->count = 0;
	return (env_list);
}

void	ft_add_env_var(t_env_list *env_list, char *name,
	char *value, int is_export)
{
	t_env_node	*new_node;
	t_env_node	*current;

	if (!env_list || !name)
		return ;
	new_node = (t_env_node *)gc_malloc(sizeof(t_env_node));
	if (!new_node)
		return ;
	new_node->name = gc_strdup(name);
	if (value)
		new_node->value = gc_strdup(value);
	else
		new_node->value = gc_strdup("");
	new_node->is_export = is_export;
	new_node->next = NULL;
	if (!env_list->head)
		env_list->head = new_node;
	else
	{
		current = env_list->head;
		while (current->next)
			current = current->next;
		current->next = new_node;
	}
	env_list->count++;
}

void	init_env(t_env_list *env_list)
{
	extern char	**environ;
	char		**env;
	char		*equal;
	char		*name;
	char		*value;

	env = environ;
	while (*env)
	{
		equal = ft_strchr(*env, '=');
		if (equal)
		{
			name = gc_substr(*env, 0, equal - *env);
			value = gc_strdup(equal + 1);
			ft_add_env_var(env_list, name, value, 1);
		}
		env++;
	}
}

void	set_env_var(t_env_list *env_list, char *name, char *value)
{
	t_env_node	*current;

	current = env_list->head;
	while(current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name + 1)) == 0)
		{
			current->value = gc_strdup(value);
			return ;
		}
		current = current->next;
	}
	return ;
}

char	*get_env_value(t_env_list *env_list, char *name)
{
	t_env_node	*current;

	current = env_list->head;
	while (ft_strncmp(current->name, name, ft_strlen(name + 1)) != 0)
		current = current->next;
	return (current->value);
}

int	ft_env(t_env_list *env_list)
{
	t_env_node	*current;

	if (!env_list)
		return (1);
	current = env_list->head;
	while (current)
	{
		ft_putstr_fd(current->name, 1);
		ft_putchar_fd('=', 1);
		ft_putendl_fd(current->value, 1);
		current = current->next;
	}
	return (0);
}
