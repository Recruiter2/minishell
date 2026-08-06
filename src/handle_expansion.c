/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 02:15:53 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/06 15:44:44 by marhuber         ###   ########.fr       */
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

/*
in this scope str points to the char right AFTER '$', also when the function 
	calls extract_var_expan()
If '?' comes at the start, this function consumes only '?'
*/
size_t	pipe_status(char *str, t_ctx *ctx, char **seg)
{
	char	*val;

	if (!str)
		return (0);
	if (str[0] == '?')
	{
		val = evar_expansion(ctx, "?");
		if (val)
			append_word(seg, val);
		return (1);
	}
	return (extract_var_expan(str, ctx, seg));
}

//	return i; consumed identifier length
//	stops before any character that cannot be part of an identifier
size_t	extract_var_expan(char *str, t_ctx *ctx, char **seg)
{
	size_t	i;
	char	*name;
	char	*val;

	if (!str)
		return (0);
	i = 0;
	if (str[i] == '_' || ft_isalpha(str[i]))
		i++;
	else
		return (0);
	while (str[i] == '_' || ft_isalnum(str[i]))
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
