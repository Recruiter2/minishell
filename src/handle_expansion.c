/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 02:15:53 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/06 00:58:29 by tzinaliy         ###   ########.fr       */
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
static	int	is_ident_start(char c)
{
	return (c == '_' || ft_isalpha(c));
}

static	int	is_ident_char(char c)
{
	return (c == '_' || ft_isalnum(c));
}

//	return i; consumed identifier length (stops before '=')
size_t	extract_var_expan(char *str, t_ctx *ctx, char **seg)
{
	size_t	i;
	char	*name;
	char	*val;

	i = 0;
	if (!str || !is_ident_start(str[0]))
		return (0);
	while (str[i] && is_ident_char(str[i]))
		i++;
	name = malloc(i + 1);
	if (!name)
		return (0);
	ft_memcpy(name, str, i);
	name[i] = '\0';
	val = evar_expansion(ctx, name);
	if (val)
		append_word(seg, val);
	free(name);
	return (i);
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
