/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:48:13 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/17 16:35:23 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**ft_split(char const *s, char c);
void	free_all(char ***strs);
size_t	ft_strlen(const char *s);

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

/**
* tries to find the executable in the current working directory [...]
* if not found tries to find it in PATH
* if found in PATH, the executable is given an absolute PATH 
* if not found in PATH does not do anything
*/
int	find_cmd(char **path, char **argv)
{
	char	*tmp;

	if (access(*argv, F_OK))
	{
		while (*path)
		{
			tmp = ft_strjoin(*path, *argv);
			if (!tmp)
				return (1);
			if (access(tmp, F_OK))
			{
				free(tmp);
				path++;
			}
			else
			{
				free(*argv);
				*argv = tmp;
				return (0);
			}
		}
	}
	return (0);
}
