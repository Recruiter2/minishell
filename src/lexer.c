/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:17:07 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/22 00:21:22 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lexer.c -- minimal lexer for minishell (conceptual, small)

#include "../includes/minishell.h"

t_token	*tok_new(t_token_type type, char *text, char quote)
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

// Consume quoted string starting at s[i] (quote char q aka " or '). 
// Returns new i (after closing quote) and sets out text (malloced).
// code comments : skip opening quote
// contents only end of in code comment
// ft has the pointer to the word (out) so it's as if we return word.
int	consume_quoted(const char *s, int i, char **out)
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
t_token	*append_token(t_token	*tail, t_token	*t)
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
int	push_op(t_token	**head, t_token	**tail, token_type type)
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

int	ft_isspace_pp(char c, int *i)
{
	if (ft_isspace(c))
	{
		(*i)++;
		return (0);
	}
	return (1);
}

void	init_lex(int *i, t_token **head, t_token **tail)
{
	*i = 0;
	*head = NULL;
	*tail = NULL;
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

// the whole point of lexer is to give the type of the input 
// and for now just remove spaces
// but by return type we already can see it return a linked list of tokens
// code comment : what is head and tail
// head is is the head of linked list and tail is the last element of it
// we wrote them for convenience so we don't have to reinvent each time
// head and tail so we can use it without thinking too much right away
t_token	*lexer(char *str)
{
	int		i;
	t_token	*head;
	t_token	*tail;
	int		res;

	init_lex(&i, &head, &tail);
	while (str[i])
	{
		if (ft_isspace_pp(str[i], &i) == 0)
			continue ;
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
		if (get_unquoted_word(str, &i, &head, &tail) == -1)
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
