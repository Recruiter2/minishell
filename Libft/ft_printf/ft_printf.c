/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:16:00 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/04/10 00:57:11 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_varformat(va_list args, char c)
{
	int		count;

	count = 0;
	if (c == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (c == 's')
		count += ft_putstr(va_arg(args, const char *));
	else if (c == 'p')
		count += ft_putptr(va_arg(args, void *));
	else if (c == 'd' || c == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (c == 'u')
		count += ft_put_us_int(va_arg(args, int));
	else if (c == 'x')
		count += ft_hex_low(va_arg(args, unsigned long));
	else if (c == 'X')
		count += ft_hex_upper(va_arg(args, int));
	else if (c == '%')
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *str, ...)
{
	int		count;
	int		i;
	va_list	args;

	va_start(args, str);
	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			count += ft_varformat(args, str[i]);
		}
		else
		{
			count += ft_putchar(str[i]);
		}
		i++;
	}
	va_end(args);
	return (count);
}
