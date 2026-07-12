/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:42:26 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/08 14:47:04 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char *p = malloc(n + 1);
	if (!p) 
		return NULL;
	ft_memcpy(p, s, n);
	p[n] = '\0';
	return p;
}