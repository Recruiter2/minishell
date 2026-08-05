/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 02:15:53 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/05 22:29:59 by tzinaliy         ###   ########.fr       */
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
static int is_ident_start(char c)
{
	return (c == '_' || ft_isalpha(c));
}

static int is_ident_char(char c)
{
	return (c == '_' || ft_isalnum(c));
}

//	return i; consumed identifier length (stops before '=')
size_t extract_var_expan(char *str, t_ctx *ctx, char **seg)
{
	size_t i = 0;
	char   *name;
	char *val;
	
	if (!str || !is_ident_start(str[0]))
		return 0;
	while (str[i] && is_ident_char(str[i]))
		i++;
	name = malloc(i + 1);
	if (!name)
		return 0;
	ft_memcpy(name, str, i);
	name[i] = '\0';
	val = evar_expansion(ctx, name);
	if (val)
		append_word(seg, val);
	free(name);
	return i;
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
	//txt[start] = ' ';
	txt[start + 1] = '\0';
	append_word(seg, txt);
	return (start);
}

//it's not really detecting the start we scoop the var to expand n add it to seg
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
			i += tmp + find_end(&str[i]);
		}
		else
		{
			i += get_one_word(&str[i], seg);
			continue ;
		}
		i++;
	}
}
