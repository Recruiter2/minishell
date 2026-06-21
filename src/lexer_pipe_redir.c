/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_pipe_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 23:34:53 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/20 23:58:27 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_choice(t_token	*head, t_token	*tail, char c)
{
	t_token_type	res;

	if (c == '<')
		res = T_REDIR_IN;
	else
		res = T_REDIR_OUT;
	return (push_op(&head, &tail, res));
}

int	pipe_(char *str, int *i, t_token **head, t_token **tail)
{
	if (str[*i] == '|')
	{
		if (!push_op(head, tail, T_PIPE))
			return (free_tokens_list(*head), -1);
		return ((*i)++, 1);
	}
	return (0);
}
// the whole point of this function is to determine if the current str[i]
// is a pipe heredoc redir append, redir in, redir out
// then it adds to our token res
// this way we build our tokens echo "str" | wc... or rather their types
// what is tail for probably to know the end...
// head is needed for check it exist
// tail is used to add in the end

int	pipe_less_more_(char *str, int *i, t_token **head, t_token **tail)
{
	int	res;

	res = pipe_(str, i, head, tail);
	if (res != 0)
		return (res);
	if (str[*i] == '<' || str[*i] == '>')
	{
		if (str[*i] == '<' && str[*i + 1] == '<')
		{
			if (!push_op(head, tail, T_HEREDOC))
				return (free_tokens_list(*head), -1);
			return (*i += 2, 1);
		}
		if (str[*i] == '>' && str[*i + 1] == '>')
		{
			if (!push_op(head, tail, T_REDIR_APPEND))
				return (free_tokens_list(*head), -1);
			return (*i += 2, 1);
		}
		if (!redirect_choice(*head, *tail, str[*i]))
			return (free_tokens_list(*head), -1);
		return ((*i)++, 1);
	}
	return (0);
}
