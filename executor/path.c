/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:48:13 by marhuber          #+#    #+#             */
/*   Updated: 2026/06/06 15:51:57 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "executor.h"

char	**ft_split(char const *s, char c);
void	free_all(char ***strs);

static size_t	ft_strlen(const char *s)
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

int	add_backslash(char **path)
{
	char	*tmp2;
	char	**it;

	it = path;
	while (*it)
	{
		tmp2 = ft_strjoin(*it, "/");
		if (!tmp2)
			return (1);
		free(*it);
		*it = tmp2;
		it++;
	}
	return (0);
}

int	read_envp(char **envp, t_ctx *ctx)
{
	char	**tmp1;

	ctx->envp = envp;
	while (*envp)
	{
		if (!ft_strncmp("PATH=", *envp, 5))
			break ;
		envp++;
	}
	tmp1 = ft_split(*envp, '=');
	if (!tmp1)
		return (1);
	ctx->path = ft_split(tmp1[1], ':');
	free_all(&tmp1);
	if (!ctx->path)
		return (1);
	return (add_backslash(ctx->path));
}
