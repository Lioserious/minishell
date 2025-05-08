/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_help.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 16:50:46 by mimalek           #+#    #+#             */
/*   Updated: 2025/05/08 15:59:00 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*get_env_value(t_env_list *env_list, char *name)
{
	t_env_node	*current;

	current = env_list->head;
	while (ft_strncmp(current->name, name, ft_strlen(name + 1)) != 0)
		current = current->next;
	return (current->value);
}

void	set_env_var(t_env_list *env_list, char *name, char *value)
{
	t_env_node	*current;

	current = env_list->head;
	while (current)
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

char	**convert_env_struct_array(t_env_list *env_list)
{
	t_env_node	*current;
	char		**env_array;
	char		*name_array;
	int			i;

	current = env_list->head;
	i = 0;
	while (current)
	{
		i++;
		current = current->next;
	}
	env_array = (char **)gc_malloc(sizeof(char *) * (i + 1));
	current = env_list->head;
	i = 0;
	while (current)
	{
		name_array = gc_strjoin(current->name, "=");
		env_array[i++] = gc_strjoin(name_array, current->value);
		current = current->next;
	}
	env_array[i] = NULL;
	return (env_array);
}
