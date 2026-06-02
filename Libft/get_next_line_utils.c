/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:52:21 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/05/11 18:25:05 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s, char const *s0)
{
	size_t	l;
	size_t	l0;
	char	*r;
	char	*start;

	l = ft_strlen(s);
	l0 = ft_strlen(s0);
	r = malloc((l + l0 + 1) * sizeof(char));
	if (!r)
		return (NULL);
	start = r;
	while (*s)
		*r++ = *s++;
	while (*s0)
		*r++ = *s0++;
	*r++ = '\0';
	return (start);
}

char	*extract_line(char *buffer)
{
	size_t	len;
	size_t	i;
	char	*res;

	len = 0;
	i = 0;
	while (buffer[len] && buffer[len] != '\n')
		len++;
	if (buffer[len] == '\n')
		len++;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = buffer[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*trim_buffer(char *buffer)
{
	size_t	line_len;
	size_t	i;
	char	*remaining;

	line_len = 0;
	i = 0;
	while (buffer[line_len] && buffer[line_len] != '\n')
		line_len++;
	if (buffer[line_len] == '\n')
		line_len++;
	remaining = malloc((ft_strlen(buffer) - line_len + 1) * sizeof(char));
	if (!remaining)
		return (NULL);
	while (i < ft_strlen(buffer) - line_len)
	{
		remaining[i] = buffer[i + line_len];
		i++;
	}
	remaining[i] = '\0';
	if (remaining && remaining[0] == '\0')
		return (free(remaining), NULL);
	return (remaining);
}

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*s;

	s = (char *)str;
	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (s + i);
		i++;
	}
	return (NULL);
}
