/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_fts.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/20 13:48:47 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/21 23:27:01 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// purpose is to recognise WORD or quoted token starting at ni = new index
// what this code do why free txt? what is txt?
// this code extracts a quoted word (aka "hi")
// we free txt because it is memory allocated in consume quote via strdup
// txt is the quoted extracted word (aka "hello")
// code comment : unmatched quote if ni < 0
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
			return (free_tokens_list(*head), -1);
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

int	loop_word(char *str, int *i, char *inner, t_token	**head)
{
	int	ni;

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
	return (0);
}

// unquoted word: run until space or operator
// looks like we needd the start because it is before the word?
// allow embedded quoted parts inside word
// we will include the quotes' contents inline; to keep lexer simple,
// just advance index
// drop — parser will reconstruct properly; here we keep raw slice uh what?
// simplify  needs
int	get_unquoted_word(char *str, int *i, t_token **head, t_token **tail)
{
	int		start;
	char	*inner;
	char	*txt;
	t_token	*token;
	int		res;

	start = *i;
	txt = NULL;
	token = NULL;
	inner = NULL;
	res = loop_word(str, i, inner, head);
	if (res != 0)
		return (-1);
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
