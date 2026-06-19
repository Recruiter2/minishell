/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:17:07 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/20 00:32:48 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lexer.c -- minimal lexer for minishell (conceptual, small)

#include "../includes/minishell.h"

static t_token	*tok_new(token_type type, char *text, char quote)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
	{
		free(text);
		return (NULL);
	}
	token->type = type;
	token->text = text;
	token->quote = quote;
	token->next = NULL;
	return (token);
}

// Consume quoted string starting at s[i] (quote char q). Returns new i (after closing quote) and sets out text (malloced).
// skip opening quote
// contents only
// a revoir
static int	consume_quoted(const char *s, int i, char **out)
{
	char	q;
	int		start;

	q = s[i];
	start = ++i;
	while (s[i])
	{
		if (s[i] == q)
		{
			*out = ft_strndup(s + start, i - start);
			return (i + 1);
		}
		if (q == '"' && s[i] == '\\' && s[i + 1])
			i += 2;
		else
			i++;
	}
	return (-1);
}
// unmatched quote

// allow escaped char in double quotes
// unmatched quote
// Append token to list tail; returns new tail or NULL on error
static t_token	*append_token(t_token	*tail, t_token	*t)
{
	if (!t)
		return (tail);
	if (tail)
		tail->next = t;
	return (t);
}

// free list and the allocated token
void	free_tokens_list(t_token	*head)
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
// free the token struct allocated in tok_new

// create and append an operator token; returns 0 on OOM
static int	push_op(t_token	**head, t_token	**tail, token_type type)
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
static int	redirect_choice(t_token	*head, t_token	*tail, char c)
{
	token_type	res;

	if (c == '<')
		res = T_REDIR_IN;
	else
		res = T_REDIR_OUT;
	return (push_op(&head, &tail, res));
}

// the whole point of this function is to determine if the current str[i]
// is a pipe heredoc redir append, redir in, redir out
// then it adds to our token res
// this way we build our tokens echo "str" | wc... or rather their types
// what is tail for probably to know the end...
// head is needed for check it exist
// tail is used to add in the end
int	pipe_less_more_(const char *str, int *i, t_token	**head, t_token	**tail)
{
	if (str[*i] == '|')
	{
		if (!push_op(head, tail, T_PIPE))
			return (free_tokens_list(*head), -1);
		(*i)++;
		return (1);
	}
	if (str[*i] == '<' || str[*i] == '>')
	{
		if (str[*i] == '<' && str[*i + 1] == '<')
		{
			if (!push_op(head, tail, T_HEREDOC))
				return (free_tokens_list(*head), -1);
			*i += 2;
			return (1);
		}
		if (str[*i] == '>' && str[*i + 1] == '>')
		{
			if (!push_op(head, tail, T_REDIR_APPEND))
				return (free_tokens_list(*head), -1);
			*i += 2;
			return (1);
		}
		if (!redirect_choice(*head, *tail, str[*i]))
			return (free_tokens_list(*head), -1);
		(*i)++;
		return (1);
	}
	return (0);
}

// purpose is to recognise WORD or quoted token starting at ni = new index
// what this code do why free txt? what is txt?
int	extract_quoted_word(const char *str, int *i, t_token	**head, t_token	**tail)
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
int	extract_unquoted_word(const char *str, int *i, t_token	**head,
		t_token	**tail)
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
// foreign extract unquoted
/* Assumes:
	- consume_quoted(const char *s, int idx,
	char **out) returns index after closing quote (>=0) or -1 on error,
	allocates *out on success.
	- ft_isspace, ft_strndup, tok_new, append_token exist.
	- t_token	is your token type.
*/

// skip escaped char
// take substring start..i-1 doesn't make sense since there is no start i -1

// the whole point of lexer is to give the type of the input and for now just remove spaces
// but by return type we already can see it return a linked list of tokens
t_token	*lexer(const char *str)
{
	int		i;
	t_token	*head;
	t_token	*tail;
	int		res;

	i = 0;
	head = NULL;
	tail = NULL;
	while (str[i])
	{
		if (ft_isspace((unsigned char)str[i]))
		{
			i++;
			continue ;
		}
		res = pipe_less_more_(str, &i, &head, &tail);
		if (res == -1)
			return (NULL);
		if (res == 1)
			continue ;
		res = extract_quoted_word(str, &i, &head, &tail);
		if (res == -1)
			return (NULL);
		if (res == 1)
			continue ;
		res = extract_unquoted_word(str, &i, &head, &tail);
		if (res == -1)
			return (NULL);
	}
	return (head);
}

// in the end we will try to achieve something like this
// char **cmds;
/*	cmd[0][0] = grep;
	cmd[0][1] = money;
	cmd[1][2] = cl;
	cmd[1][3] = -cw;
*/
// or else
