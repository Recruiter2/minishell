/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 14:42:26 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/04 12:12:27 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	char	*p;

	p = malloc(n + 1);
	if (!p)
		return (NULL);
	ft_memcpy(p, s, n);
	p[n] = '\0';
	return (p);
}
