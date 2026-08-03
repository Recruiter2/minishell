/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:34:54 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/03 17:04:24 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 || *s2)
	{
		if (*s1 - *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
	}
	return (0);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (*s1 || *s2))
	{
		if (*s1 - *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		i++;
	}
	return (0);
}

int	ft_isalpha(char c)
{
	if (65 <= c && c <= 90)
	{
		return (1);
	}
	if (97 <= c && c <= 122)
	{
		return (1);
	}
	return (0);
}

int	ft_isalnum(char c)
{
	if (48 <= c && c <= 57)
	{
		return (1);
	}
	if (65 <= c && c <= 90)
	{
		return (1);
	}
	if (97 <= c && c <= 122)
	{
		return (1);
	}
	return (0);
}

int	simple_atoi(int *ptr_to_n, const char *str)
{
	int	n;
	int	s;
	int	i;

	n = 0;
	s = 1;
	if (*str == '-')
	{
		str++;
		s = -1;
	}
	else if (*str == '+')
		str++;
	i = 0;
	while ('0' <= *str && *str <= '9')
	{
		n = 10 * n;
		n += *str++ - '0';
		i++;
	}
	if (*str || i == 0)
		return (1);
	*ptr_to_n = n * s;
	return (0);
}
