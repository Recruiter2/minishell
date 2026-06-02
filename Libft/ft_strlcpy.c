/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 12:37:55 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/16 15:30:00 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	srclen;
	size_t	i;

	i = 0;
	srclen = ft_strlen(src);
	if (size == 0)
	{
		return (srclen);
	}
	if (size == 1)
	{
		dest[0] = '\0';
		return (srclen);
	}
	while (*src && (i < (size - 1)))
	{
		*dest++ = *src++;
		i++;
	}
	*dest++ = '\0';
	return (srclen);
}
