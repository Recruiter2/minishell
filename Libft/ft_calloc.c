/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:16:30 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/04/27 17:37:34 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t n, size_t size)
{
	size_t	i;
	char	*res;
	size_t	bytes;

	i = 0;
	bytes = size * n;
	res = malloc(bytes);
	if (!res)
		return (NULL);
	while (i < bytes)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}
/*
int	main()
{
	size_t n = 1;
	size_t size = 1;
	ft_calloc(n, size);
}
*/
