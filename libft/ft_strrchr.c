/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:36:18 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/15 13:26:12 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			i;
	unsigned char	cc;

	cc = (unsigned char) c;
	i = ft_strlen(s);
	if (cc == '\0')
		return ((char *)(s + i));
	while (i > 0)
	{
		if (s[i - 1] == (unsigned char)c)
		{
			return ((char *)(s + i - 1));
		}
		i--;
	}
	return (NULL);
}
