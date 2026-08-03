/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 02:15:53 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/03 19:52:36 by tzinaliy         ###   ########.fr       */
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

//detect if $ in target (variable expansion)
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
