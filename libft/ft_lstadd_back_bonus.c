/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:32:33 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/14 19:41:06 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*content;

	content = *lst;
	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (content -> next != NULL)
		content = content -> next;
	content -> next = new;
}
