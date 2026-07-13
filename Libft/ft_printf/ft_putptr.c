/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:25:46 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/07/13 00:45:54 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_hex_lx(unsigned long nbr)
{
	char		*dict;
	int			count;

	count = 0;
	dict = "0123456789abcdef";
	if (nbr >= 16)
	{
		count += ft_hex_lx(nbr / 16);
		count += ft_hex_lx(nbr % 16);
	}
	else
	{
		count += ft_putchar(dict[nbr]);
	}
	return (count++);
}

int	ft_putptr(void *ptr)
{
	int	count;

	if (!ptr)
	{
		ft_printf("%s", "(nil)");
		return (5);
	}
	count = 0;
	count = ft_putstr("0x");
	count += ft_hex_lx((unsigned long)ptr);
	return (count);
}
