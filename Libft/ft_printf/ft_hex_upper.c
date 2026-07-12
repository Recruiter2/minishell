/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_upper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:24:06 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/11/27 17:24:12 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_hex_upper(unsigned int nbr)
{
	char		*dict;
	int			count;

	count = 0;
	dict = "0123456789ABCDEF";
	if (nbr >= 16)
	{
		count += ft_hex_upper(nbr / 16);
		count += ft_hex_upper(nbr % 16);
	}
	else
	{
		count += ft_putchar(dict[nbr]);
	}
	return (count);
}
