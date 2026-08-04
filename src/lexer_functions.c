/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 23:25:40 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/04 06:23:39 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// create and append an operator token; returns 0 on OOM
int	push_op(t_token	**head, t_token	**tail, t_token_type type)
{
	t_token	*token;

	token = tok_new(type, NULL, 0);
	if (!token)
		return (0);
	if (!*head)
		*head = token;
	*tail = append_token(*tail, token);
	return (1);
}

//functions seems useless at this point
//this function skips space
int	ft_isspace_pp(char c, int *i)
{
	if (ft_isspace(c))
	{
		(*i)++;
		return (0);
	}
	return (1);
}

// this function is used to set to 0 or initialize the i, head, tail
// values
void	init_lex(int *i, t_token **head, t_token **tail)
{
	*i = 0;
	*head = NULL;
	*tail = NULL;
}

void	free_tokens(t_token	*head)
{
	t_token	*p;
	t_token	*n;

	p = head;
	while (p)
	{
		n = p->next;
		free(p->text);
		free(p);
		p = n;
	}
}
