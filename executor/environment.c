/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 21:40:05 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/16 19:57:00 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "environment.h"

char	**ft_split(char const *s, char c);
void	free_all(char ***strs);
int		split_in_two(char *str, char c, char *result[2]);
char	*join_str_c_str(char const *s1, char c, char const *s2);
t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *newelem);
int		ft_lstsize(t_list *lst);
int		add_all_bi(t_list_bi **builtins);

static int	evar_strs_to_lst(t_list_ev **ptr_env_lst, char **envp)
{
	char		**strs;
	t_evar		*content;
	t_list_ev	*tmp;
	char		*single_evar[2];

	strs = envp;
	*ptr_env_lst = NULL;
	while (*strs)
	{
		content = malloc (sizeof(*content));
		if (!content)
			return (1); // perror?
		if (split_in_two(*strs, '=', single_evar))
			return (1);
		content->name = single_evar[0];
		content->value = single_evar[1];
		tmp = ft_lstnew(content);
		if (!tmp)
			return (1);
		ft_lstadd_back(ptr_env_lst, tmp);
		strs++;
	}
	return (0);
}

int	evar_lst_to_strs(t_ctx *ctx)
{
	t_list_ev	*it_lst;
	t_evar		*evar;
	char		**it_strs;
	int			n;

	n = ft_lstsize(ctx->env_lst);
	free_all(&ctx->env_strs);
	ctx->env_strs = malloc(sizeof(*ctx->env_strs) * (n + 1));
	if (!ctx->env_strs)
		return (1);
	it_lst = ctx->env_lst;
	it_strs = ctx->env_strs;
	while (n--)
	{
		evar = it_lst->content;
		*it_strs = join_str_c_str(evar->name, '=', evar->value);
		if (!*it_strs)
			return (free_all(&ctx->env_strs), 1);
		it_strs++;
		it_lst = it_lst->next;
	}
	*it_strs = NULL;
	return (0);
}

int	init_ctx(t_ctx *ctx, char **envp)
{
	if (evar_strs_to_lst(&ctx->env_lst, envp))
		return (1);
	ctx->env_strs = NULL;
	if (evar_lst_to_strs(ctx))
		return (1);
	ctx->path = NULL;
	if (add_all_bi(&ctx->builtins))
		return (1);
	ctx->exit_status = 0;
	return (0);
}
