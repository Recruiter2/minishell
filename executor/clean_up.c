/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_up.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 20:12:19 by marhuber          #+#    #+#             */
/*   Updated: 2026/06/28 20:42:45 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "prepare_execution.h"

void	destroy(t_full_cmd **ptr_cmd)
{
	t_full_cmd *cmd;

	cmd = *ptr_cmd;
	ft_lstclear(&cmd->file_in, &free);
	ft_lstclear(&cmd->file_out, &free);
	ft_lstclear(&cmd->cmd, &free);
	free(cmd);
	cmd = NULL;
}

void	end(t_ctx *ctx, t_full_cmd *cmd)
{
	ctx++;
	destroy(&cmd);
}
