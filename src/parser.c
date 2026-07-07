#include "../includes/minishell.h"

void add_arg(t_cmd *cmd, char *word)
{
	cmd->argc++;
	cmd->argv = realloc(cmd->argv, sizeof(char *) * (cmd->argc + 1));
	cmd->argv[cmd->argc - 1] = word; // assume token->text ownership stays valid
	cmd->argv[cmd->argc] = NULL;
}

t_cmd *new_cmd(void)
{
	t_cmd *cmd = calloc(1, sizeof(*cmd));
	cmd->argv = NULL;
	cmd->argc = 0;
	return cmd;
}

t_cmd *parse_pipeline(t_token *tok, int *out_count)
{
	t_cmd  *cmds = NULL;
	int	 n = 0;

	t_cmd *cur = new_cmd();

	for (; tok; tok = tok->next)
	{
		if (tok->type == T_PIPE)
		{
			// finalize current command
			cmds = realloc(cmds, sizeof(t_cmd) * (n + 1));
			cmds[n++] = *cur;
			free(cur);

			cur = new_cmd();
			continue;
		}

		// Redirections should be handled separately (not argv)
		if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
			|| tok->type == T_REDIR_APPEND || tok->type == T_HEREDOC)
		{
			// skip operator token already tokenized as its own T_... with tok->next
			// then consume the target WORD (filename/limiter) as part of redirection parsing
			// (You’ll implement: parse_redir(tok, &cur, &tok) that advances tok.)
			continue;
		}

		if (tok->type == T_WORD)
			add_arg(cur, tok->text);
	}

	// push last command
	cmds = realloc(cmds, sizeof(t_cmd) * (n + 1));
	cmds[n++] = *cur;
	free(cur);

	*out_count = n;
	return cmds;
}
