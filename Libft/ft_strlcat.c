/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 22:30:29 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/17 10:01:15 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	lensrc;
	size_t	lendest;
	int		i;

	lensrc = ft_strlen(src);
	lendest = ft_strlen(dest);
	i = 0;
	if (size < lendest)
		return (lensrc + size);
	if (lendest > size)
		return (lendest + lensrc);
	if (lendest == size)
		return (lendest + lensrc);
	while (src[i] && ((lendest + i) < (size - 1)))
	{
		dest[lendest + i] = src[i];
		i++;
	}
	dest[lendest + i] = '\0';
	return (lendest + lensrc);
}
