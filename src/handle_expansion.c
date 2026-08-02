/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 02:15:53 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/02 16:57:01 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// notes
/* rewrite existing functions doesn't matter if already written 
write long enough to remember to add to libft not in lib thus rewrite
so the whole point one function detect if $

call another function this function will take into param the address of the segment to add to
that's about it

so the current logic 
t->text == '$' //roughly not accurate ; means symbol detected
then 
call this function
append_word(&seg, evar_expansion(ctx, &t->text));
so it will be something among the lines of
if $
while s != ' ' i ++
//*/


#include "../includes/minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

//detect if $ in target
int detect_var_expan(char *str)
{
	size_t i = 0;

	while(str[i])
	{
		if (str[i] == '$')
			return 1;
		i++;
	}
	return 0;
}

//assuming not just expansion symbol so we have some var to expand
//we will handle just symbol in a different function
size_t	extract_var_expan(char *str, t_ctx *ctx, char **seg)
{
	size_t	start = 0;
	size_t	end = 0;
	char *res;

	while (str[end] && str[end] != ' ')
		end++;
	res = malloc(end - start + 1);
	ft_memcpy(res, str, end - start);
	res[end - start + 1] = '\0'; // or maybe overkill no need terminating char
	append_word(seg, evar_expansion(ctx, res));
	return end - start;
}

int	find_end(char *str)
{
	size_t	i = 0;


	while (str[i])
	{
		if (str[i] == ' ')
			return i;
		i++;
	}
	return 0;
}

int	get_one_word(char *str, char **seg)
{
	char*txt;
	size_t	start = 0;
	size_t	end = find_end(str) + 1;

	txt = ft_strndup(str + start, end - start);
	while (start < end)
	{
		txt[start] = str[start];
		start++;
	}
	txt[start] = ' ';
	txt[start + 1] = '\0';

	append_word(seg, txt);

	return (start);
}
//it's not really detecting the start we scoop the varto expand n add it to seg
/* altho it detects the var to expand
and then if not detect just adds what needed
//*/
void	detect_start(char *str, t_ctx *ctx, char **seg)
{
	size_t	i = 0;
	size_t	tmp;

	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = extract_var_expan(&str[i + 1], ctx, seg);
			i += tmp + 1;
		}
		else
		{
			i += get_one_word(&str[i], seg);
			continue;
		}
		i++;
	}
}
/*so right now we write a parser in a parser or it looks like it 
in fact lexer was already written it breaks down input into tokens but 
smh we en up with this input "afs dfs sdaf" and it is count as one token 
by the lexer so we need to process it further down in case we have 
"$afs dfs $sdaf"
to expand the vars
so we need to loop through this magnificient code 
if last one was space then expand the variable
//*/

/*//function to extract word but it's possible to write own so no much need in this
int	get_unquoted_word(char *str, t_token **head, t_token **tail)
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
//*/
