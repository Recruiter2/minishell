/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:15:45 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/11/13 21:15:48 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h> 
#include <stdarg.h>
#include <limits.h>

int	ft_printf(const char *str, ...);

int	ft_putchar(char c);

int	ft_putstr(const char *str);

int	ft_putptr(void *ptr);

int	ft_putnbr(long long n);

int	ft_put_us_int(unsigned int nbr);

int	ft_hex_low(unsigned int nbr);

int	ft_hex_upper(unsigned int nbr);
