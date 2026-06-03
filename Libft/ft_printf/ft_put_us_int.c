/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_us_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:27:04 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/04/11 01:01:59 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put_us_int(unsigned int nb)
{
	int	count;

	count = 0;
	if (nb <= 9)
		count += ft_putchar(nb + 48);
	if (nb >= 10)
	{
		count += ft_putnbr(nb / 10);
		count += ft_putchar(nb % 10 + 48);
	}
	return (count);
}
