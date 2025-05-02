/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstring.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:04:36 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:04:38 by lihrig           ###   ########.fr       */
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
