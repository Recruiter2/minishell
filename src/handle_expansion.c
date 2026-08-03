/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 02:15:53 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/03 23:35:11 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/* the whole point of this file is to store function that 
handle the variable expansion*/
//detect if $ in target (variable expansion)
int	detect_var_expan(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

//assuming not just expansion symbol so we have some var to expand
//we will handle just symbol in a different function
size_t	extract_var_expan(char *str, t_ctx *ctx, char **seg)
{
	size_t	start;
	size_t	end;
	char	*res;

	start = 0;
	end = 0;
	while (str[end] && str[end] != ' ')
		end++;
	res = malloc(end - start + 1);
	ft_memcpy(res, str, end - start);
	res[end - start + 1] = '\0';
	append_word(seg, evar_expansion(ctx, res));
	return (end - start);
}

int	find_end(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (i);
		i++;
	}
	return (0);
}

int	get_one_word(char *str, char **seg)
{
	char	*txt;
	size_t	start;
	size_t	end;

	start = 0;
	end = find_end(str) + 1;
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
	size_t	i;
	size_t	tmp;

	i = 0;
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
			continue ;
		}
		i++;
	}
}
