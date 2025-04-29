/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 11:35:21 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/15 12:31:54 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	free_list(t_list *lst, void (*del)(void *))
{
	t_list	*p_h;

	while (lst != NULL)
	{
		p_h = lst -> next;
		del(lst -> content);
		free(lst);
		lst = p_h;
	}
}

static t_list	*create_new_n(void *(*f)(void *),
void *content, void (*del)(void *))
{
	t_list	*new_n;

	new_n = (t_list *)malloc(sizeof(t_list));
	if (new_n == NULL)
		return (NULL);
	new_n -> content = f(content);
	if (new_n -> content == NULL)
	{
		del(new_n);
		free(new_n);
		return (NULL);
	}
	new_n -> next = NULL;
	return (new_n);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_l;
	t_list	*new_n;
	t_list	*prev_n;
	t_list	*current;

	new_l = NULL;
	prev_n = NULL;
	current = lst;
	while (current != NULL)
	{
		new_n = create_new_n(f, current -> content, del);
		new_n -> next = NULL;
		if (new_n == NULL)
		{
			free_list(new_l, del);
			return (NULL);
		}
		if (new_l == NULL)
			new_l = new_n;
		else
			prev_n -> next = new_n;
		prev_n = new_n;
		current = current -> next;
	}
	return (new_l);
}
