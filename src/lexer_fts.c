/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 13:48:47 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/20 15:09:47 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	redirect_choice(t_token	*head, t_token	*tail, char c)
{
	token_type	res;

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
	int res;

	res = pipe_(str, i, head, tail);
	if (res != 0)
		return res;
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

// purpose is to recognise WORD or quoted token starting at ni = new index
// what this code do why free txt? what is txt?
int	extract_quoted_word(char *str, int *i, t_token **head, t_token **tail)
{
	t_token	*token;
	int		ni;
	char	*txt;

	txt = NULL;
	if (str[*i] == '\'' || str[*i] == '"')
	{
		ni = consume_quoted(str, *i, &txt);
		if (ni < 0)
			return (free_tokens_list(*head), -1); // unmatched quote
		token = tok_new(T_WORD, txt, str[*i]);
		if (!token)
		{
			free(txt);
			return (free_tokens_list(*head), -1);
		}
		if (!head)
			head = &token;
		*tail = append_token(*tail, token);
		*i = ni;
		return (1);
	}
	return (0);
}

// unquoted word: run until space or operator
// looks like we needd the start because it is before the word?
// allow embedded quoted parts inside word
// we will include the quotes' contents inline; to keep lexer simple,
// just advance index
// drop — parser will reconstruct properly; here we keep raw slice uh what?
// simplify  needs
int	extract_unquoted_word(char *str, int *i, t_token	**head, t_token	**tail)
{
	int		start;
	char	*inner;
	int		ni;
	char	*txt;
	t_token	*token;

	start = *i;
	txt = NULL;
	token = NULL;
	ni = 0;
	while (str[*i] && !ft_isspace((unsigned char)str[*i]) && str[*i] != '|'
		&& str[*i] != '<' && str[*i] != '>')
	{
		inner = NULL;
		if (str[*i] == '\'' || str[*i] == '"')
		{
			ni = consume_quoted(str, *i, &inner);
			if (ni < 0)
				return (free(inner), free_tokens_list(*head), -1);
			i = &ni;
			free(inner);
		}
		else
		{
			if (str[*i] == '\\' && str[*i + 1])
				*i += 2;
			else
				(*i)++;
		}
	}
	txt = ft_strndup(str + start, *i - start);
	if (!txt)
		return (free_tokens_list(*head), -1);
	token = tok_new(T_WORD, txt, 0);
	if (!token)
		return (free(txt), free_tokens_list(*head), -1);
	if (*head == NULL)
		*head = token;
	*tail = append_token(*tail, token);
	return (0);
}