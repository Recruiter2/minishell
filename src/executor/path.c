/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:48:13 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/11 10:31:38 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/environment.h"

void		free_all(char ***strs);
int			split_in_two(char *str, char c, char *result[2]);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*join_str_c_str(char const *s1, char c, char const *s2);
int			put_str_fd(const char *s, int fd);

/*
This function deletes first any existing collection of strings with the PATH.
Then it searches among the environment variables (in ther string format) for 
	the variable PATH, presuming it might contain updated data.
If found, the fonction extracts from the value of PATH its elements, which are 
	separated by ':'-chars.
It saves the new elements of PATH as a collection of strings.
*/
int	extract_path(t_ctx *ctx)
{
	char	**it;
	char	*tmp[2];

	free_all(&ctx->path);
	it = ctx->env_strs;
	while (*it)
	{
		if (ft_strncmp("PATH=", *it, 5) == 0)
			break ;
		it++;
	}
	if (!*it)
		return (0);
	if (split_in_two(*it, '=', tmp))
		return (1);
	free(tmp[0]);
	ctx->path = ft_split(tmp[1], ':');
	free(tmp[1]);
	if (!ctx->path)
		return (1);
	return (0);
}

/*
Cf section "3.7.2 Command Search and Execution" in bash manual
This fonction tries to find a simple command (e.g. without args) in the PATH.
It tries to access an executable with the name searched for in each folder 
	in the PATH.
If it finds one, then substitutes *argv (e.g. argv[0]) with the absolute path of 
	said executable.
If the search is unsuccesfull (or if the PATH collection of strings is 
	unavailable), it outputs an error.
*/
int	find_cmd(char **path, char **argv)
{
	char	*tmp;

	if (path)
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
	put_str_fd("minishell: command not found: ", 2);
	put_str_fd(*argv, 2);
	return (put_str_fd("\n", 2), 127);
}
