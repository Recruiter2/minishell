#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "minishell.h"

/* Your project already has these types + lexer output. */

/* If you already have is_redir() in your project, you can remove this one. */
int is_redir(t_token_type t)
{
	return (t == T_REDIR_IN || t == T_REDIR_OUT || t == T_REDIR_APPEND || t == T_HEREDOC);
}

static void append_word(char **seg, const char *w)
{
	size_t seglen = (*seg) ? strlen(*seg) : 0;
	size_t wlen = w ? strlen(w) : 0;

	char *newseg;
	size_t add = wlen + (seglen ? 1 : 0);

	if (!w || w[0] == '\0')
		return;

	newseg = realloc(*seg, seglen + add + 1);
	if (!newseg) exit(1);

	*seg = newseg;
	if (seglen)
		strcat(*seg, " ");
	strcat(*seg, w);
}

static char *dup_or_empty(const char *s)
{
	if (!s) return strdup("");
	return strdup(s);
}

/*
** Build pipeline segments as strings of "cmd args" only:
** - Words only (T_WORD)
** - Split on T_PIPE
** - Redirections ignored here (we’ll print them separately)
**
** Returns NULL-terminated array: {"grep et", "wc -l", NULL}
*/
static char **build_res_list_words_only(t_token *head)
{
	int nseg = 1;
	for (t_token *t = head; t; t = t->next)
		if (t->type == T_PIPE)
			nseg++;

	char **res = calloc(nseg + 1, sizeof(char*));
	int idx = 0;

	char *seg = NULL;
	for (t_token *t = head; t; t = t->next)
	{
		if (t->type == T_PIPE)
		{
			res[idx++] = seg ? dup_or_empty(seg) : strdup("");
			free(seg);
			seg = NULL;
			continue;
		}
		if (t->type == T_WORD)
		{
			if (t->text && t->text[0] != '\0')
				append_word(&seg, t->text);
		}
	}

	res[idx] = seg ? dup_or_empty(seg) : strdup("");
	free(seg);
	return res;
}

static void debug_print_tokens(t_token *tokens)
{
	printf("TOKENS: ");
	for (t_token *t = tokens; t; t = t->next)
	{
		printf("[type=%d", (int)t->type);
		if (t->text)
			printf(", text=\"%s\"", t->text);
		if (t->quote)
			printf(", quote='%c'", t->quote);
		printf("] ");
	}
	printf("\n");
}

static void debug_apply_redirs_only_print(t_token *tokens)
{
	for (t_token *t = tokens; t; t = t->next)
	{
		if (!is_redir(t->type))
			continue;

		if (!t->next || t->next->type != T_WORD || !t->next->text)
			continue;

		if (t->type == T_REDIR_IN)
			printf("DEBUG_CALL: add_file_in(full_cmd, \"%s\")\n", t->next->text);
		else if (t->type == T_REDIR_OUT)
			printf("DEBUG_CALL: add_file_out(full_cmd, \"%s\", 0)\n", t->next->text);
		else if (t->type == T_REDIR_APPEND)
			printf("DEBUG_CALL: add_file_out(full_cmd, \"%s\", 1)\n", t->next->text);
		else if (t->type == T_HEREDOC)
			printf("DEBUG_CALL: (HEREDOC) type=%d with delimiter \"%s\"\n", (int)t->type, t->next->text);
	}
}

static void debug_add_pipeline_cmds_print_only(t_full_cmd *full_cmd, t_token *tokens)
{
	char **res = build_res_list_words_only(tokens);
	if (!res)
		return;

	printf("SEGMENTS (cmd+args only):\n");
	for (int i = 0; res[i]; i++)
		printf("  seg[%d] = \"%s\"\n", i, res[i]);

	printf("DEBUG_EXECUTOR CALLS:\n");
	for (int i = 0; res[i]; i++)
	{
		char **first_cmd = ft_split(res[i], ' ');
		printf("  DEBUG_CALL: first_cmd = ft_split(\"%s\", ' ')\n", res[i]);
		printf("  DEBUG_CALL: add_single_cmd(full_cmd, first_cmd)\n");

		/* If you want to actually call add_single_cmd, uncomment and make sure ft_split matches your project allocations. */
		/* if (first_cmd && first_cmd[0]) add_single_cmd(full_cmd, first_cmd); */

		/* TODO: free first_cmd properly if your project provides it. */
		/* free_split(first_cmd); */
	}

	/* free res[i] and res itself (if your project doesn't already do it) */
	for (int i = 0; res[i]; i++)
		free(res[i]);
	free(res);
}

/* Public: creates full_cmd (optional) and prints what it would do */
t_full_cmd *dispatch_dbg(t_token *tokens)
{
	t_full_cmd *full_cmd = initialize_cmd();
	if (!full_cmd)
		return NULL;

	debug_print_tokens(tokens);

	printf("\n");
	debug_apply_redirs_only_print(tokens);

	printf("\n");
	debug_add_pipeline_cmds_print_only(full_cmd, tokens);

	return full_cmd;
}
