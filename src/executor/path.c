/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:48:13 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/02 13:13:26 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/environment.h"

void		free_all(char ***strs);
int			split_in_two(char *str, char c, char *result[2]);
char		**ft_split(char const *s, char c);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*join_str_c_str(char const *s1, char c, char const *s2);
void		put_str_fd(const char *s, int fd);

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
	return(0);
}

/**
3.7.2 Command Search and Execution
After a command has been split into words, if it results in a simple command and an
optional list of arguments, the shell performs the following actions.
1. If the command name contains no slashes, the shell attempts to locate it. If there exists
a shell function by that name, that function is invoked as described in Section 3.3 [Shell
Functions], page 19.
2. If the name does not match a function, the shell searches for it in the list of shell
builtins. If a match is found, that builtin is invoked.
3. If the name is neither a shell function nor a builtin, and contains no slashes, Bash
searches each element of $PATH for a directory containing an executable file by that
name. Bash uses a hash table to remember the full pathnames of executable files to
avoid multiple PATH searches (see the description of hash in Section 4.1 [Bourne Shell
Builtins], page 52). Bash performs a full search of the directories in $PATH only if the
command is not found in the hash table. If the search is unsuccessful, the shell searches
for a defined shell function named command_not_found_handle. If that function exists,
it is invoked in a separate execution environment with the original command and the
original command’s arguments as its arguments, and the function’s exit status becomes
the exit status of that subshell. If that function is not defined, the shell prints an error
message and returns an exit status of 127.
4. If the search is successful, or if the command name contains one or more slashes, the
shell executes the named program in a separate execution environment. Argument 0
is set to the name given, and the remaining arguments to the command are set to the
arguments supplied, if any.
5. If this execution fails because the file is not in executable format, and the file is not a
directory, it is assumed to be a shell script, a file containing shell commands, and the
shell executes it as described in Section 3.8 [Shell Scripts], page 50.
6. If the command was not begun asynchronously, the shell waits for the command to
complete and collects its exit status.
*/
int	find_cmd(char **path, char **argv)
{
	char	*tmp;

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
	put_str_fd("minishell: command not found: ", 2);
	put_str_fd(*argv, 2);
	put_str_fd("\n", 2);
	return (127);
}
