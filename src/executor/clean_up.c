/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:12:19 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/13 14:50:25 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/executor.h"
#include <stdio.h>

void	ft_lstclear(t_list **ptlst, void (*del)(void*));
void	free_tokens(t_token	*head);
void	free_all(char ***strs);

void	destroy_single_cmd(void *content)
{
	t_single_cmd	*cmd;

	cmd = content;
		//fprintf(stderr, "destroy_single_cmd content=%p argv=%p\n", (void*)cmd, (void*)cmd->argv);
	ft_lstclear(&cmd->redir, &free);
	free_all(&cmd->argv);
	free(content);

}

void	destroy_full_cmd(t_full_cmd **ptr_cmd)
{
	t_full_cmd	*cmd;

	cmd = *ptr_cmd;
	ft_lstclear(&cmd->cmd, &destroy_single_cmd);
	free_tokens(cmd->tokens);
	free(cmd);
	cmd = NULL;
}

void	destroy_evar(void *content)
{
	t_evar	*evar;

	evar = content;
	free(evar->name);
	free(evar->value);
	free(content);
}

void	free_ctx_ressources(t_ctx *ctx)
{
	close(ctx->fd_stdin);
	close(ctx->fd_stdout);
	ft_lstclear(&ctx->env_lst, &destroy_evar);
	free_all(&ctx->env_strs);
	ft_lstclear(&ctx->builtins, &free);
	free_all(&ctx->path);
}

void	end(t_ctx *ctx, t_full_cmd *cmd)
{
	if (cmd)
		destroy_full_cmd(&cmd);
	free_ctx_ressources(ctx);
}
