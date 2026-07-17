/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:34:54 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/17 08:42:50 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (*s1 || *s2)
	{
		if (*s1 - *s2)
			return (*(unsigned char *)s1 - *(unsigned char *)s2);
		s1++;
		s2++;
		i++;
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

size_t	ft_strlen(const char *s)
{
	const char	*it;

	it = s;
	while (*it)
		it++;
	return (it - s);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*p;
	char	*re;

	len = ft_strlen(s1) + ft_strlen(s2);
	re = malloc(sizeof(*re) * (len + 1));
	if (!re)
		return (perror("malloc error"), NULL);
	p = re;
	while (*s1)
	{
		*p = *s1;
		p++;
		s1++;
	}
	while (*s2)
	{
		*p = *s2;
		p++;
		s2++;
	}
	*p = 0;
	return (re);
}

char	*ft_strdup(const char *src)
{
	char	*dup;
	char	*it;

	dup = malloc(sizeof(*src) * (ft_strlen(src) + 1));
	if (!dup)
		return (0);
	it = dup;
	while (*src)
	{
		*it = *src;
		it++;
		src++;
	}
	*it = 0;
	return (dup);
}

int	split_in_two(char *str, char c, char *result[2])
{
	char	*separator;
	char	*it;

	separator = str;
	while (*separator != 0 && *separator != c)
		separator++;
	result[1] = ft_strdup(separator + 1);
	if (!result[1])
		return (1);
	result[0] = malloc(sizeof(char) * (separator - str + 1));
	if (!result[0])
		return (free(result[1]), 1);
	it = result[0];
	while (str < separator)
		*it++ = *str++;
	*it = 0;
	return (0);
}

char	*join_str_c_str(char const *s1, char c, char const *s2)
{
	size_t	len;
	char	*p;
	char	*re;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	re = malloc(sizeof(*re) * (len + 1));
	if (!re)
		return (perror("malloc error"), NULL);
	p = re;
	while (*s1)
	{
		*p = *s1;
		p++;
		s1++;
	}
	*p = c;
	p++;
	while (*s2)
	{
		*p = *s2;
		p++;
		s2++;
	}
	*p = 0;
	return (re);
}

const char	*ft_strchr(const char *str, char c)
{
	while (*str)
	{
		if (*str == c)
			return (str);
		str++;
	}
	if (c == 0)
		return (str);
	else
		return (NULL);
}
