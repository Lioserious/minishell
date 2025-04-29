/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:41:50 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/13 17:45:40 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_length;
	size_t	i;

	dest_length = ft_strlen(dst);
	i = 0;
	if (dest_length >= size)
		return (ft_strlen(src) + size);
	while (size - 1 > dest_length + i && src[i] != '\0')
	{
		dst[dest_length + i] = src[i];
		i++;
	}
	dst[dest_length + i] = '\0';
	return (dest_length + ft_strlen(src));
}
