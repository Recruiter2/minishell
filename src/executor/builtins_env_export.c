/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env_export.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 18:19:18 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/02 16:31:12 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/environment.h"

int			ft_isalpha(char c);
int			ft_isalnum(char c);
int			ft_strcmp(const char *s1, const char *s2);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *newelem);
const char	*ft_strchr(const char *str, char c);
int			split_in_two(char *str, char c, char *result[2]);
void		put_str_fd(const char *s, int fd);
int			bi_env(char **argv, t_ctx *ctx);

/*
◦ env with no options or arguments

print the environment
*/

int	bi_env(char **argv, t_ctx *ctx)
{
	t_list_ev	*it_lst;
	t_evar		*evar;

	(void)argv;
	it_lst = ctx->env_lst;
	while (it_lst)
	{
		evar = it_lst->content;
		printf("%s=%s\n", evar->name, evar->value);
		it_lst = it_lst->next;
	}
	return (0);
}

/*
◦ export with no options

	export [name[=value]]
Mark each name to be passed to subsequently executed commands in the en-
vironment.
If no names are supplied export displays a list of names of all exported
	variables on the standard output.
export allows the value of a variable to be set at the same time it is exported 
	by following the variable name with =value.
The return status is zero unless an invalid option is supplied, one of the 
	names is not a valid shell variable name.

name	A word consisting solely of letters, numbers, and underscores, and 
	beginning with a letter or underscore. Names are used as shell variable and 
	function names.
*/

static int	is_valid_identifier(char *str)
{
	if (*str != '_' && !ft_isalpha(*str))
		return (0);
	str++;
	while (*str)
	{
		if (*str != '_' && !ft_isalnum(*str))
			return (0);
		str++;
	}
	return (1);
}

int	export_valid_var(char *name, char *value, t_list_ev **ptr_env_lst)
{
	t_list_ev	*it_lst;
	t_list_ev	*new;
	t_evar		*evar;

	it_lst = *ptr_env_lst;
	while (it_lst)
	{
		evar = it_lst->content;
		if (ft_strcmp(evar->name, name) == 0)
		{
			evar->value = value;
			free(name);
			return (0);
		}
		it_lst = it_lst->next;
	}
	evar = malloc(sizeof(*evar));
	if (!evar)
		return (free(name), free(value), perror("malloc error"), 1);
	evar->name = name;
	evar->value = value;
	new = ft_lstnew(evar);
	if (!new)
		return (free(name), free(value), free(evar), 1);
	return (ft_lstadd_back(ptr_env_lst, new), 0);
}

static int	export_var(char *str, t_list_ev **ptr_env_lst)
{
	char		*tmp[2];
	const char	*separing;

	separing = ft_strchr(str, '=');
	if (!separing)
	{
		if (is_valid_identifier(str))
			return (0);
	}
	else if (separing > str)
	{
		if (split_in_two(str, '=', tmp))
			return (1);
		if (is_valid_identifier(tmp[0]))
			return (export_valid_var(tmp[0], tmp[1], ptr_env_lst));
	}
	put_str_fd("minishell: export: `", 2);
	put_str_fd(str, 2);
	put_str_fd("': not a valid identifier\n", 2);
	return (1);
}

int	bi_export(char **argv, t_ctx *ctx)
{
	int			ret;

	if (!*++argv)
		return (bi_env(argv, ctx));
	ret = 0;
	while (*argv)
	{
		ret += export_var(*argv, &ctx->env_lst);
		argv++;
	}
	if (ret)
		return (1);
	else
		return (0);
}
