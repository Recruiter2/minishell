/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:08:52 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/19 17:25:40 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*this function converts char to int*/

static int	isspace(int c)
{
	return (((c > 8) && (c <= 13)) || c == 32);
}

int	ft_atoi(const char *c)
{
	int	sign;
	int	res;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (isspace(c[i]))
		i++;
	if (c[i] == '+' && c[i + 1] == '-')
		return (0);
	if ((c[i] == '+'))
		i++;
	if (c[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (ft_isdigit(c[i]))
	{
		res = res * 10 + c[i] - 48;
		i++;
	}
	res *= sign;
	return (res);
}
