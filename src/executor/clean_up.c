/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:12:19 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/05 12:12:29 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "prepare_execution.h"

void	free_all(char ***strs);

void	destroy(t_full_cmd **ptr_cmd)
{
	t_full_cmd	*cmd;

	cmd = *ptr_cmd;
	ft_lstclear(&cmd->redir, &free);
	ft_lstclear(&cmd->cmd, &free);
	free(cmd);
	cmd = NULL;
}

void	end(t_ctx *ctx, t_full_cmd *cmd)
{
	free_all(&ctx->path);
	if (cmd)
		destroy(&cmd);
}
