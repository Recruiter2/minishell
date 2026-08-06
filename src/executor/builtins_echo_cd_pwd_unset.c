/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_echo_cd_pwd_unset.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 21:26:49 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/06 16:13:49 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../../includes/environment.h"

int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strdup(const char *src);
int		export_valid_var(char *name, char *value, t_list_ev **ptr_env_lst);
char	*evar_expansion(t_ctx *ctx, char *name);
void	put_str_fd(const char *s, int fd);
void	destroy_evar(void *content);
void	ft_lstdelone(t_list *lst, void (*del)(void *));

/*
◦ echo with option -n

echo [-n] [arg ...]
Output the args, separated by spaces, terminated with a newline.
The return status is 0 unless a write error occurs.
If -n is specified, the trailing newline is not printed.
*/

int	bi_echo(char **argv, t_ctx *ctx)
{
	char	**start;
	char	**it;
	char	*trailing;

	(void)ctx;
	trailing = "\n";
	start = argv + 1;
	if (*start)
	{
		if (ft_strcmp(*start, "-n") == 0)
		{
			trailing = "";
			start++;
		}
		it = start;
		while (*it)
		{
			if (it != start)
				printf(" ");
			printf("%s", *it);
			it++;
		}
	}
	printf ("%s", trailing);
	return (0);
}

/*
◦ cd with only a relative or absolute path

cd [directory]
Change the current working directory to directory.
If the directory change is successful, cd sets the value of the PWD environment
	variable to the new directory name, and sets the OLDPWD environment 
	variable to the value of the current working directory before the change.
The return status is zero if the directory is successfully changed, non-zero 
	otherwise.
*/

static int	cd_valid_path(char *new_pwd, t_ctx *ctx)
{
	char	*incumbent_pwd;
	char	*varname_oldpwd;
	char	*varname_pwd;
	int		err;

	incumbent_pwd = getcwd(NULL, 0);
	varname_oldpwd = ft_strdup("OLDPWD");
	varname_pwd = ft_strdup("PWD");
	if (! incumbent_pwd || !varname_oldpwd || !varname_pwd)
	{
		free(incumbent_pwd);
		free(varname_oldpwd);
		free(varname_pwd);
		return (1);
	}
	chdir(new_pwd);
	new_pwd = getcwd(NULL, 0);
	err = 0;
	err += export_valid_var(varname_oldpwd, incumbent_pwd, &ctx->env_lst);
	err += export_valid_var(varname_pwd, new_pwd, &ctx->env_lst);
	if (err)
		return (1);
	else
		return (0);
}

int	bi_cd(char **argv, t_ctx *ctx)
{
	char	*tmp;
	char	*err_prefix;

	err_prefix = "minishell: cd: ";
	if (argv[1] == NULL)
	{
		tmp = evar_expansion(ctx, "HOME");
		if (access(tmp, F_OK))
			return (put_str_fd(err_prefix, 2), perror(tmp), free(tmp), 1);
		cd_valid_path(tmp, ctx);
		return (free(tmp), 0);
	}
	if (argv[2] != NULL)
	{
		put_str_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	if (access(argv[1], F_OK))
		return (put_str_fd(err_prefix, 2), perror(argv[1]), 1);
	cd_valid_path(argv[1], ctx);
	return (0);
}

/*
◦ pwd with no options

pwd
Print the absolute pathname of the current working directory.
*/
int	bi_pwd(char **argv, t_ctx *ctx)
{
	char	*path;

	(void)argv;
	(void)ctx;
	path = getcwd(NULL, 0);
	if (!path)
		return (perror("minishell: pwd: "), 1);
	printf("%s\n", path);
	free(path);
	return (0);
}

/*
◦ unset with no options

unset [name]
Remove each variable name.
When variables or functions are removed, they are also removed from the 
	environment passed to subsequent commands.
*/

int	bi_unset(char **argv, t_ctx *ctx)
{
	t_list_ev	*it_lst;
	t_list_ev	**ptr_to_it_lst;
	t_evar		*evar;

	argv++;
	while (*argv)
	{
		ptr_to_it_lst = &ctx->env_lst;
		it_lst = ctx->env_lst;
		while (it_lst)
		{
			evar = it_lst->content;
			if (ft_strcmp(evar->name, *argv) == 0)
			{
				*ptr_to_it_lst = it_lst->next;
				ft_lstdelone(it_lst, &destroy_evar);
				break ;
			}
			ptr_to_it_lst = &it_lst->next;
			it_lst = it_lst->next;
		}
		argv++;
	}
	return (0);
}
