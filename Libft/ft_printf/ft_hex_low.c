/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_low.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:10:21 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/11/27 17:10:26 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_low(unsigned int nbr)
{
	char		*dict;
	int			count;

	count = 0;
	dict = "0123456789abcdef";
	if (nbr >= 16)
	{
		count += ft_hex_low(nbr / 16);
		count += ft_hex_low(nbr % 16);
	}
	else
	{
		count += ft_putchar(dict[nbr]);
	}
	return (count);
}
