/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 13:26:45 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/24 13:26:47 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	count_digits(long long nb, size_t i)
{
	while (nb >= 10)
	{
		i++;
		nb = nb / 10;
	}
	return (i);
}

char	*digits_to_char(size_t i, long long n, char *res)
{
	res[i] = '\0';
	while (i--)
	{
		res[i] = n % 10 + 48;
		n /= 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char		*res;
	size_t		i;
	long long	tmp_n;
	int			sign;

	sign = 0;
	i = 1;
	tmp_n = (long long)n;
	if (!tmp_n && tmp_n != 0)
		return (NULL);
	if (tmp_n < 0)
	{
		i++;
		sign = 1;
		tmp_n *= -1;
	}
	i = count_digits(tmp_n, i);
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (0);
	res = digits_to_char(i, tmp_n, res);
	if (sign)
		res[0] = '-';
	return (res);
}
