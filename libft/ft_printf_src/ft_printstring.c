/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mimalek <mimalek@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 09:57:29 by mimalek           #+#    #+#             */
/*   Updated: 2024/10/24 11:19:26 by mimalek          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printstring(const char *s)
{
	int			i;
	const char	*null_s;

	null_s = "(null)";
	i = 0;
	if (s == NULL)
		return (ft_printstring(null_s));
	if (s[0] == '\0')
		return (0);
	while (s[i] != '\0')
	{
		if (ft_printchar(s[i]) == -1)
			return (-1);
		i++;
	}
	return (i);
}
