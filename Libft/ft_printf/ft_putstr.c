/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 21:16:00 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/07/13 00:46:50 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_putstr(const char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (!str)
	{
		ft_putstr("(null)");
		return (6);
	}
	write(1, str, len);
	return (len);
}
