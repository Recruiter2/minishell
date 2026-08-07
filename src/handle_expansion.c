/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/29 02:15:53 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/07 15:51:19 by tzinaliy         ###   ########.fr       */
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

char	*expand_one_word_token(char *token, t_ctx *ctx, int single_quote)
{
	char	*expanded;

	expanded = NULL; // append_word expects *seg to be NULL or empty
	if (!token || token[0] == '\0')
		return (NULL);

	if (detect_var_expan(token) && !single_quote)
		detect_start(token, ctx, &expanded); // fills expanded via append_word
	else
		append_word(&expanded, token);       // just duplicate/append token

	return (expanded);
}

static int argv_append_ptr(char ***argv, char *s)
{
	size_t	i;
	char	**newv;

	if (!s)
		return (1);
	if (!*argv)
	{
		*argv = ft_calloc(2, sizeof(char *));
		if (!*argv)
			return (0);
		(*argv)[0] = s;
		(*argv)[1] = NULL;
		return (1);
	}
	i = 0;
	while ((*argv)[i])
		i++;
	newv = ft_calloc(i + 2, sizeof(char *));
	if (!newv)
		return (0);
	ft_memcpy(newv, *argv, i * sizeof(char *));
	newv[i] = s;
	newv[i + 1] = NULL;
	free(*argv);
	*argv = newv;
	return (1);
}


static int	argv_push(char ***argv, char *s)
{
	int		i;

	if (!s)
		return (1);

	if (!*argv)
	{
		*argv = ft_calloc(2, sizeof(char *));
		if (!*argv)
			return (0);
		(*argv)[0] = s;
		return (1);
	}

	i = 0;
	while ((*argv)[i])
		i++;

	if (!argv_append_ptr(argv, s))
		return 0;
	return (1);
}

int	consume_word_to_argv(t_token **t, char ***argv, t_ctx *ctx)
{
	char	*expanded;
	int		single_quote;

	if (!(*t)->text || (*t)->text[0] == '\0')
	{
		*t = (*t)->next;
		return (1);
	}

	single_quote = ((*t)->quote == '\'');
	expanded = expand_one_word_token((*t)->text, ctx, single_quote);
	if (!expanded)
		return (0);

	if (!argv_push(argv, expanded))
	{
		free(expanded);
		return (0);
	}

	*t = (*t)->next;
	return (1);
}
