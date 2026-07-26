/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/26 21:26:49 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/26 22:23:54 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
◦ unset with no options

unset [name]
Remove each variable name.
When variables or functions are removed, they are also removed from the 
	environment passed to subsequent commands.
*/

#include "../../includes/environment.h"

int		ft_strcmp(const char *s1, const char *s2);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	destroy_evar(void *content);

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
