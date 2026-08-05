/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher_lib.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 20:27:08 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/05 23:00:09 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_segment(char **res, int *idx, char **seg)
{
	if (*seg)
	{
		res[(*idx)++] = *seg;
		*seg = NULL;
	}
	else
	{
		res[(*idx)++] = ft_strdup("");
	}
}

void	consume_word(t_token **t, char **seg, t_ctx *ctx)
{
	if (!(*t)->text || (*t)->text[0] == '\0')
	{
		*t = (*t)->next;
		return ;
	}
	if (*seg && (*seg)[0] != '\0')
		append_word(seg, " ");
	if (detect_var_expan((*t)->text) && (*t)->quote != '\'')
		detect_start((*t)->text, ctx, seg);
	else
		append_word(seg, (*t)->text);
}

void	consume_redir(t_token **t)
{
	if ((*t)->next && (*t)->next->type == T_WORD)
		*t = (*t)->next;
}

void	skip_other(t_token **t)
{
	*t = (*t)->next;
}
