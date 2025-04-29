/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:56:33 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/10 08:24:04 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
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
		if (s_o[i] == '\0' || s_t[i] == '\0')
			break ;
		i++;
	}
	return (0);
}
