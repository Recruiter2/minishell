/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher_lib.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 20:27:08 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/06 11:19:35 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	add_segment(char **res, int *idx, char **seg)
{
	if (*seg)
	{
		res[(*idx)++] = *seg;
		*seg = NULL;
	}
	else
	{
		res[(*idx)++] = ft_strdup("");
	}
}

void	consume_word(t_token **t, char **seg, t_ctx *ctx)
{
	if (!(*t)->text || (*t)->text[0] == '\0')
	{
		*t = (*t)->next;
		return ;
	}
	if (*seg && (*seg)[0] != '\0')
		append_word(seg, " ");
	if (detect_var_expan((*t)->text) && (*t)->quote != '\'')
		detect_start((*t)->text, ctx, seg);
	else
		append_word(seg, (*t)->text);
}

void	consume_redir(t_token **t)
{
	if ((*t)->next && (*t)->next->type == T_WORD)
		*t = (*t)->next;
}

/*expansion functions*/
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
	txt[start + 1] = '\0';
	append_word(seg, txt);
	return (start);
}

//it's not really detecting the start we scoop the var to expand n add it to seg
/* altho it detects the var to expand
and then if not detect just adds what needed*/
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
