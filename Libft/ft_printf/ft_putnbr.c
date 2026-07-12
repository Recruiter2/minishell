/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:12:17 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/11/27 17:12:22 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/* toutes les fonctions doivent retourner le nb de char imprime
 notamment cette fonction doit afficher le nb de char imprime */

int	ft_putnbr(long long nb)
{
	int			count;

	count = 0;
	if (nb < 0)
	{
		nb *= -1;
		count += ft_putchar('-');
	}
	if (nb <= 9)
		count += ft_putchar(nb + 48);
	if (nb >= 10)
	{
		count += ft_putnbr(nb / 10);
		count += ft_putchar(nb % 10 + 48);
	}
	return (count);
}
