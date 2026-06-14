/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/08 13:17:07 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/10 15:43:35 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// lexer.c -- minimal lexer for minishell (conceptual, small)

#include "../includes/minishell.h"



static token_t *tok_new(token_type type, char *text, char quote)
{
	token_t	*token;

	token = malloc(sizeof(*token));
	if (!token)
	{
		free(text);
		return NULL;
	}
	token->type = type;
	token->text = text;
	token->quote = quote;
	token->next = NULL;
	return token;
}


// Consume quoted string starting at s[i] (quote char q). Returns new i (after closing quote) and sets out text (malloced).
static int consume_quoted(const char *s, int i, char q, char **out)
{
	int start = ++i; // skip opening quote
	while (s[i]){
		if (s[i] == q)
		{
			*out = ft_strndup(s + start, i - start); // contents only
			return i + 1;
		}
		if (q == '"' && s[i] == '\\' && s[i+1])
			i += 2; // allow escaped char in double quotes
		else
			i++;
	}
	return -1; // unmatched quote
}

// Append token to list tail; returns new tail or NULL on error
static token_t *append_token(token_t *tail, token_t *t)
{
	if (!t)
		return tail;
	if (tail)
		tail->next = t;
	return t;
}

// free list and the allocated token
void	free_tokens_list(token_t *head)
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
static int push_op(token_t **head, token_t **tail, token_type type)
{
	token_t *token = tok_new(type, NULL, 0);
	if (!token)
		return 0;
	if (!*head)
		*head = token;
	*tail = append_token(*tail, token);
	return 1;
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
