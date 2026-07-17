/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:48:13 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/17 08:31:27 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "environment.h"

void		free_all(char ***strs);
int			split_in_two(char *str, char c, char *result[2]);
char		**ft_split(char const *s, char c);
int			ft_strcmp(const char *s1, const char *s2);
const char	*ft_strchr(const char *str, char c);
char		*join_str_c_str(char const *s1, char c, char const *s2);

int	extract_path(t_ctx *ctx)
{
	char	**it;
	char	*tmp[2];

	free_all(&ctx->path);
	it = ctx->env_strs;
	while (*it)
	{
		if (ft_strcmp("PATH=", *it) == 0)
			break ;
		it++;
	}
	if (!*it)
		return (0);
	if (split_in_two(*it, '=', tmp))
		return (1);
	ctx->path = ft_split(tmp[1], ':');
	free(tmp[0]);
	if (!ctx->path)
		return (1);
	return(0);
}

/**

*/
int	find_cmd(char **path, char **argv)
{
	char	*tmp;

	if (!ft_strchr(*argv, '/'))
	{
		while (*path)
		{
			tmp = join_str_c_str(*path, '/', *argv);
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
