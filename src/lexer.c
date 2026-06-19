/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:17:07 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/18 20:00:25 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lexer.c -- minimal lexer for minishell (conceptual, small)

#include "../includes/minishell.h"

static token_t	*tok_new(token_type type, char *text, char quote)
{
	token_t	*token;

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
static token_t	*append_token(t_token	*tail, t_token	*t)
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
	token_t	*p;
	token_t	*n;

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
	token_t	*token;

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
	token_t	*token;
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
	token_t	*token;

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
/*static int	extract_unquoted_word(const char *str, int *ip, t_token	**head,
		t_token	**tail)
{
	int		start;
	char	*inner;
	char	*txt;
	token_t	*token;
	int		ni;

	start = *ip;
	inner = NULL;
	txt = NULL;
	while (str[*ip] && !ft_isspace((unsigned char)str[*ip]) && str[*ip] != '|'
		&& str[*ip] != '<' && str[*ip] != '>')
	{
		if (str[*ip] == '\'' || str[*ip] == '"')
		{
			inner = NULL;
			ni = consume_quoted(str, *ip, &inner); // ni >= 0 on success 
			if (ni < 0)
			{
				free(inner);
				return (-1); // caller handles overall cleanup 
			}
			free(inner);   // we only needed to skip quoted part here 
			*ip = (int)ni; // advance past quoted part 
		}
		else
		{
			if (str[*ip] == '\\' && str[*ip + 1])
				*ip += 2;
			else
				(*ip)++;
		}
	}
	txt = ft_strndup(str + start, *ip - start);
	if (!txt)
		return (-1);
	token = tok_new(T_WORD, txt, 0);
	if (!token)
	{
		free(txt); // tok_new failed and didn't take ownership 
		return (-1);
	}
	if (*head == NULL)
		*head = token;
	*tail = append_token(*tail, token); // append_token returns new tail 
	return (0);
}
*/
// skip escaped char
// take substring start..i-1 doesn't make sense since there is no start i -1

// the whole point of lexer is to give the type of the input and for now just remove spaces
// but by return type we already can see it return a linked list of tokens
token_t	*lexer(const char *str)
{
	int		i;
	token_t	*head;
	token_t	*tail;
	int		res;
	int		start;
	/*	char	*txt;
		int		ni;

		token_t	*token;
		char	*inner;*/
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
		if (str[i] == '|')
		{
			token = tok_new(T_PIPE, NULL, 0);
			if (!token)
				goto fail;
			if (!head)
				head = token;
			tail = append_token(tail, token);
			i++;
			continue;
		}
		if (str[i] == '|') 
		{
			if (!push_op(&head, &tail, T_PIPE))
				return (free_tokens_list(head), NULL);
			i++;
			continue;
		}
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i] == '<' && str[i+1] == '<')
			{
				if (!push_op(&head, &tail, T_HEREDOC))
					return (free_tokens_list(head), NULL);
				i += 2;
				continue;
			}
			if (str[i] == '>' && str[i+1] == '>')
			{
				if (!push_op(&head, &tail, T_REDIR_APPEND))
					return (free_tokens_list(head), NULL);
				i += 2;
				continue;
			}
			if (!push_op(&head, &tail, str[i] == '<' ? T_REDIR_IN : T_REDIR_OUT))
				return (free_tokens_list(head), NULL);
			i++;
			continue;
		}

		// WORD or quoted ; ni = new index //what this code do why free txt? what is txt?
		if (str[i] == '\'' || str[i] == '"')
		{
			char q = str[i];
			char *txt = NULL;
			int ni = consume_quoted(str, i, q, &txt);
			if (ni < 0)
				goto fail; // unmatched quote
			token = tok_new(T_WORD, txt, q);
			if (!token)
			{
				free(txt);
				goto fail;
			}
			if (!head)
				head = token;
			tail = append_token(tail, token);
			i = ni;
			continue;
		}

		// unquoted word: run until space or operator
		int start = i;
		while (str[i] && !ft_isspace((unsigned char)str[i]) &&
			str[i] != '|' && str[i] != '<' && str[i] != '>')
		{
			if (str[i] == '\'' || str[i] == '"')
			{ // allow embedded quoted parts inside word
				char q = str[i];
				char *inner = NULL;
				int ni = consume_quoted(str, i, q, &inner);
				if (ni < 0)
				{
					free(inner);
					goto fail;
				}
				// we will include the quotes' contents inline; to keep lexer simple, just advance index
				i = ni;
				free(inner); // drop — parser will reconstruct properly; here we keep raw slice
			} 
			else
			{
				if (str[i] == '\\' && str[i+1]) i += 2; // skip escaped char
				else i++;
			}
		}
		// take substring start..i-1
		char *txt = ft_strndup(str + start, i - start);
		if (!txt)
			goto fail;
		token = tok_new(T_WORD, txt, 0);
		if (!token)
		{
			free(txt);
			goto fail;
		}
		if (!head)
			head = token;
		tail = append_token(tail, token);
	}
	return head;

fail:
	// free list
	free_tokens_list(head);
	return NULL;
}

// how could fail be replace if exitis not good?
// in the end we will try to achieve something like this
// char **cmds;
/*	cmd[0][0] = grep;
	cmd[0][1] = money;
	cmd[1][2] = cl;
	cmd[1][3] = -cw;
*/
// or else

/*
int	pipe_less_more_(const char *str, int *i, t_token	**head, t_token	**tail)
{
	if (!str || !i || !head || !tail)
		return (-1);
	if (str[*i] == '|')
	{
		if (!push_op(head, tail, T_PIPE))
		{
			free_tokens_list(*head);
			return (-1);
		}
		(*i)++;
		return (1);
	}
	if (str[*i] == '<' || str[*i] == '>')
	{
		if (str[*i] == '<' && str[*i + 1])
		{
			if (str[*i + 1] == '<')
			{
				if (!push_op(head, tail, T_HEREDOC))
				{
					free_tokens_list(*head);
					return (-1);
				}
				*i += 2;
				return (1);
			}
		}
		if (str[*i] == '>' && str[*i + 1])
		{
			if (str[*i + 1] == '>')
			{
				if (!push_op(head, tail, T_REDIR_APPEND))
				{
					free_tokens_list(*head);
					return (-1);
				}
				*i += 2;
				return (1);
			}
		}
		if (!redirect_choice(*head, *tail, str[*i]))
		{
			free_tokens_list(*head);
			return (-1);
		}
		(*i)++;
		return (1);
	}
	return (0);
}
*/

/*if (str[i] == '|')
		{
			if (!push_op(&head, &tail, T_PIPE))
				return (free_tokens_list(head), NULL);
			i++;
			continue ;
		}
		if (str[i] == '<' || str[i] == '>')
		{
			if (str[i] == '<' && str[i + 1] == '<')
			{
				if (!push_op(&head, &tail, T_HEREDOC))
					return (free_tokens_list(head), NULL);
				i += 2;
				continue ;
			}
			if (str[i] == '>' && str[i + 1] == '>')
			{
				if (!push_op(&head, &tail, T_REDIR_APPEND))
					return (free_tokens_list(head), NULL);
				i += 2;
				continue ;
			}
			if (!redirect_choice(head, tail, str[i]))
				return (free_tokens_list(head), NULL);
			i++;
			continue ;
		}*/
/*res = pipe_less_more_(str, &i, &head, &tail);
if (res == -1)
	return (NULL);
if (res == 1)
	continue ;*/