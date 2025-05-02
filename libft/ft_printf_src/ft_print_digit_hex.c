/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_digit_hex.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lihrig <lihrig@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 12:03:39 by lihrig            #+#    #+#             */
/*   Updated: 2025/05/02 12:03:40 by lihrig           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_digit_hex_upp(unsigned int n)
{
	int	output;

	output = to_hex_upp(n);
	if (output == -1)
		return (-1);
	else
		return (output);
}

int	ft_print_digit_hex_low(unsigned int n)
{
	int	output;

	output = to_hex_low(n);
	if (output == -1)
		return (-1);
	else
		return (output);
}
