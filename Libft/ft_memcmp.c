/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 19:40:02 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/17 20:53:58 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *str, const void *str0, size_t n)
{
	size_t			res;
	size_t			i;
	unsigned char	*s;
	unsigned char	*s0;

	i = 0;
	res = 0;
	s = (unsigned char *)str;
	s0 = (unsigned char *)str0;
	if (n == 0)
		return (0);
	while (i < n)
	{
		res = s[i] - s0[i];
		if (res != 0)
			return (res);
		i++;
	}
	return (res);
}
