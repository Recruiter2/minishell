/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:22:00 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/03 21:16:48 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int is_redir(t_token_type t)
{
	return (t == T_REDIR_IN || t == T_REDIR_OUT || t == T_REDIR_APPEND || t == T_HEREDOC);
}

//this function appends word to the segment that will be used obviously
// no need to grow: existing + (space if needed) + word + '\0'
//strlcpy copy old content obviously
void append_word(char **seg, char *word)
{
	char	*temp;
	size_t	seglen = 0;
	size_t	wlen;
	size_t	add = 0;

	if (word == NULL)
		return;
	wlen = ft_strlen(word);
	add = wlen;
	if (*seg)
	{
		seglen = ft_strlen(*seg);
		add++;
	}
	temp = ft_calloc(seglen + add + 1, sizeof(char));
	if (!temp)
		exit(1);
	if (*seg)
	{
		ft_strlcpy(temp, *seg, seglen + 1);
		free(*seg);
	}
	*seg = temp;
	if (seglen)
		ft_strcat(*seg, " ");
	ft_strcat(*seg, word);
}

//nseg increments so we count the number of segments
//echo hi | text.txt two segments here
int	number_of_segments(t_token *head)
{
	t_token *t = head;
	int nseg = 0;

	if (!head)
		return 0;
	while (t != NULL)
	{
		if (t->type == T_PIPE)
			nseg++;
		t = t->next;
	}
	nseg++; // segments = pipes + 1 (assuming at least one token)
	return (nseg);
}

// returns a NULL-terminated array of strings: e.g. {"grep et","wc -l",NULL}
// First pass: count how many pipeline segments (pipes split segments)
// +1 for NULL terminator
//t = t->next; advance before continue
//is_redir(t->type) skip redirection target token (typically the next T_WORD)
char **build_res_list(t_token *head, t_ctx *ctx)
{
	t_token *t;
	int idx;
	int nseg;
	char **res;
	char *seg;

	t = head;
	idx = 0;
	nseg = number_of_segments(head);
	res = ft_calloc(nseg + 1, sizeof(char *));
	seg = NULL;

	while (t != NULL)
	{
		if (t->type == T_PIPE)
		{
			add_segment(res, &idx, &seg);
			t = t->next;
		}
		else if (t->type == T_WORD)
			consume_word(&t, &seg, ctx);
		else if (is_redir(t->type))
			consume_redir(&t);
		else
			skip_other(&t);
	}
	add_segment(res, &idx, &seg);
	return res;
}