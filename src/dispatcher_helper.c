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

int is_redir(t_token_type t)
{
	return (t == T_REDIR_IN || t == T_REDIR_OUT || t == T_REDIR_APPEND || t == T_HEREDOC);
}

void append_word(char **seg, const char *w)
{
	size_t seglen = (*seg) ? strlen(*seg) : 0;
	size_t wlen = strlen(w);

	// grow: existing + (space if needed) + word + '\0'
	size_t add = wlen + (seglen ? 1 : 0);
	char *newseg = realloc(*seg, seglen + add + 1);
	if (!newseg) exit(1);

	*seg = newseg;
	if (seglen) strcat(*seg, " ");
	strcat(*seg, w);
}

// returns a NULL-terminated array of strings: e.g. {"grep et","wc -l",NULL}
char **build_res_list(t_token *head)
{
	// First pass: count how many pipeline segments (pipes split segments)
	int nseg = 0;
	for (t_token *t = head; t; t = t->next) {
		if (t->type == T_PIPE) nseg++;
	}
	nseg++; // segments = pipes + 1 (assuming at least one token)

	char **res = calloc(nseg + 1, sizeof(char*)); // +1 for NULL terminator
	int idx = 0;

	char *seg = NULL;

	for (t_token *t = head; t; t = t->next)
	{
		if (t->type == T_PIPE) {
			res[idx++] = seg ? seg : strdup("");
			seg = NULL;
			continue;
		}

		/*if (t->type == T_WORD) {
			append_word(&seg, t->text);
			continue;
		}*/
		if (t->type == T_WORD) {
		if (!t->text || t->text[0] == '\0')
			continue;
		append_word(&seg, t->text);
		continue;
}


		if (is_redir(t->type)) {
			// skip redirection target token (typically the next T_WORD)
			if (t->next && t->next->type == T_WORD)
				t = t->next;
			continue;
		}
	}

	// last segment
	res[idx] = seg ? seg : strdup("");
	return res; // caller frees each res[i] and res itself
}