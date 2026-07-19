/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:22:00 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/07/13 14:22:03 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int is_redir(t_token_type t)
{
	return (t == T_REDIR_IN || t == T_REDIR_OUT || t == T_REDIR_APPEND || t == T_HEREDOC);
}

//what is w? word god damn it
void append_word(char **seg, char *word)
{
	char	*temp;
	size_t	seglen = 0;
	size_t	wlen = ft_strlen(word);
	size_t	add = 0;


	// grow: existing + (space if needed) + word + '\0'
	if (*seg)
	{
		seglen = ft_strlen(*seg);
		add = wlen + 1;
	}
	temp = ft_calloc(seglen + add + 1, sizeof(char));
	if (!temp)
		exit(1);
	if (*seg)
	{
		ft_strlcpy(temp, *seg, seglen + 1); // copy old content
		free(*seg);
	}
	*seg = temp;
	if (seglen) //seems logic is flawed should add space if seglen so not so flawed
		ft_strcat(*seg, " "); //do we have an str cat function?  
	ft_strcat(*seg, word);
}

int	number_of_segments(t_token *head)
{
	t_token *t = head;
	int nseg = 0;

	if (!head)
		return 0;
	while (t != NULL)
	{
		if (t->type == T_PIPE)
			nseg++;//what is this ig we get multiple segment if we have a pipe say la la | grep t we have two but for echo hi we only have one...
		t = t->next;
	}
	nseg++; // segments = pipes + 1 (assuming at least one token)
	return (nseg);
}
// returns a NULL-terminated array of strings: e.g. {"grep et","wc -l",NULL}
char **build_res_list(t_token *head)
{
	// First pass: count how many pipeline segments (pipes split segments)
	t_token *t = head;
	int nseg = number_of_segments(head);

	//printf("we got number of segmets nseg = %d\n", nseg);
	char **res = ft_calloc(nseg + 1, sizeof(char*)); // +1 for NULL terminator
	int idx = 0;

	char *seg = NULL;

	t = head;
	while (t != NULL)
	{
		//printf("t->type = %d\n", (int)t->type);
		if (t->type == T_PIPE)
		{
			if (seg)
				res[idx++] = seg;
			else
				res[idx++] = strdup("");
			seg = NULL;
			t = t->next;// advance before continue
			continue;
		}

		if (t->type == T_WORD)
		{
			if (!t->text || t->text[0] == '\0')
			{
				t = t->next;// advance before continue
				continue;
			}
			append_word(&seg, t->text);
			t = t->next;// advance before continue
			continue;
		}
		//printf("t->type=%d text='%s' is_redir=%d\n", (int)t->type, t->text, is_redir(t->type));

		if (is_redir(t->type))
		{
			// skip redirection target token (typically the next T_WORD)
			if (t->next && t->next->type == T_WORD)
				t = t->next;
			t = t->next;// advance before continue
			continue;
		}
		t = t->next;
	}

	// last segment
	if (seg)
		res[idx] = seg;
	else
		res[idx] = strdup("");
	return res; // caller frees each res[i] and res itself
}