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
		return tail;
	if (tail)
		tail->next = t;
	return t;
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
	token_t *token = tok_new(type, NULL, 0);
	if (!token)
		return 0;
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

//the whole point of lexer is to give the type of the input and for now just remove spaces
//but by return type we already can see it return a linked list of tokens
token_t *lexer(const char *str)
{
	int i = 0;
	token_t *head;
	token_t *tail;
	token_t *token;

	head = NULL;
	tail = NULL;
	while (str[i])
	{
		if (ft_isspace((unsigned char)str[i]))
		{
			i++;
			continue;
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