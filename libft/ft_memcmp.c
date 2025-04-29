/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 11:19:43 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/13 18:20:05 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*s_o;
	unsigned char	*s_t;
	size_t			i;

	s_o = (unsigned char *)s1;
	s_t = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s_o[i] != s_t[i])
			return (s_o[i] - s_t[i]);
		i++;
	}
	return (0);
}
