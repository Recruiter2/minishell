/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 12:54:25 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/17 14:50:20 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		i;
	char	*s;
	char	*res;

	s = (char *)str;
	i = 0;
	res = NULL;
	if (!ft_isascii(c))
		c = (unsigned char)c;
	while (s[i])
	{
		if (s[i] == c)
			res = s + i;
		i++;
	}
	if (res)
		return (res);
	if (c == '\0')
	{
		if (s[i] == c)
			return (s + i);
	}
	return (res);
}
