/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/22 00:32:18 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/07/22 01:55:13 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//the point of filler is to add the $; variable of expansion
#include "../includes/minishell.h"

void	add_expandable_var(t_ctx *ctx, t_token *head)
{
	t_token *t;

	t = head;
	while (t != NULL)
	{

		if (t->type == T_WORD)
		{
			if (!t->text || t->text[0] == '\0')
			{
				t = t->next;// advance before continue
				continue;
			}
			
			if (t->text[0] == '$')
			{
				printf("t->text = %s\n", t->text);
				evar_expansion(ctx, t->text);
			}
			t = t->next;// advance before continue
			continue;
		}
		//printf("t->type=%d text='%s' is_redir=%d\n", (int)t->type, t->text, is_redir(t->type));

		t = t->next;
	}
	return ;
}