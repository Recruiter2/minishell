/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:12:19 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/19 20:14:52 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/environment.h"
#include "../../includes/prepare_execution.h"

void	ft_lstclear(t_list **ptlst, void (*del)(void*));
void	free_all(char ***strs);

void	destroy_cmd(t_full_cmd **ptr_cmd)
{
	t_full_cmd	*cmd;

	cmd = *ptr_cmd;
	ft_lstclear(&cmd->redir, &free);
	ft_lstclear(&cmd->cmd, &free);
	free(cmd);
	cmd = NULL;
}

void	delete_evar(void *content)
{
	t_evar	*evar;

	evar = content;
	free(evar->name);
	free(evar->value);
	free(content);
}

void	free_ctx_ressources(t_ctx *ctx)
{
	ft_lstclear(&ctx->env_lst, &delete_evar);
	free_all(&ctx->env_strs);
	ft_lstclear(&ctx->builtins, &free);
	free_all(&ctx->path);
}

void	end(t_ctx *ctx, t_full_cmd *cmd)
{
	if (cmd)
		destroy_cmd(&cmd);
	free_ctx_ressources(ctx);
}
