/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 14:56:58 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/17 16:57:51 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *str, const char *str0, size_t size)
{
	int		res;
	size_t	i;

	i = 0;
	res = 0;
	if (!size)
		return (0);
	while (*str && *str0 && (i < (size - 1)))
	{
		res = (unsigned char)*str++ - (unsigned char)*str0++;
		if (res != 0)
		{
			return (res);
		}
		i++;
	}
	return ((unsigned char)*str - (unsigned char)*str0);
}
