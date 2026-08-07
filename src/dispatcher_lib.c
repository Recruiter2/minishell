/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher_lib.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/03 20:27:08 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/07 23:51:23 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

size_t	pipe_status(char *str, t_ctx *ctx, char **seg);

// consume BOTH the operator and its filename *t = fname->next;
void	consume_redir(t_full_cmd *full, t_token **t)
{
	t_token	*redir;
	t_token	*fname;

	redir = *t;
	if (!redir || !redir->next)
		return ;
	fname = redir->next;
	if (fname->type != T_WORD)
		return ;
	if (redir->type == T_REDIR_IN)
		add_file_in(full, fname->text);
	else if (redir->type == T_REDIR_OUT)
		add_file_out(full, fname->text, 0);
	else if (redir->type == T_REDIR_APPEND)
		add_file_out(full, fname->text, 1);
	else if (redir->type == T_HEREDOC)
		add_here_doc(full, redir->next->text);
	*t = fname->next;
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
//i += tmp; // + find_end(&str[i]); previously
void	detect_start(char *str, t_ctx *ctx, char **seg)
{
	size_t	i;
	size_t	tmp;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			tmp = pipe_status(&str[i + 1], ctx, seg);
			i += tmp;
		}
		else
		{
			i += get_one_word(&str[i], seg);
			continue ;
		}
		i++;
	}
}
