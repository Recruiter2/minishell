#include <stdio.h>
#include "../includes/tokens.h"
#include "../includes/prepare_execution.h"


static void	print_token_snapshot(t_token *tokens)
{
	int i = 0;

	printf("tokens=%p\n", (void*)tokens);
	while (tokens && i < 50)
	{
		printf("  token[%d]=%p type=%d str=%s\n",
			i, (void*)tokens, tokens->type,
			tokens->text ? tokens->text : "(null)");
		tokens = tokens->next;
		i++;
	}
	if (i == 50)
		printf("  ... token log truncated\n");
}

static int	list_single_cmd_len(t_list_single_cmd *head)
{
	int n = 0;
	while (head)
	{
		n++;
		head = head->next;
	}
	return n;
}

static void	print_argv(char **argv)
{
	int i = 0;

	if (!argv)
	{
		printf("    argv=NULL\n");
		return;
	}
	while (argv[i] && i < 100)
	{
		printf("    argv[%d]=%s (%p)\n", i, argv[i], (void*)argv[i]);
		i++;
	}
	if (i == 0)
		printf("    argv[0] is NULL\n");
	if (i == 100)
		printf("    ... argv log truncated\n");
}

void	print_full_cmd(t_full_cmd *cmd)
{
	t_list_single_cmd *node;
	int idx = 0;

	if (!cmd)
	{
		printf("cmd=NULL\n");
		return;
	}
	printf("full_cmd=%p\n", (void*)cmd);
	printf("  cmd->tokens=%p\n", (void*)cmd->tokens);
	printf("  cmd->cmd(list head)=%p\n", (void*)cmd->cmd);
	printf("  cmd list length ~ %d\n", list_single_cmd_len(cmd->cmd));

	print_token_snapshot(cmd->tokens);

	node = cmd->cmd;
	while (node && idx < 100)
	{
		t_single_cmd *sc = node->content; // adjust if your node uses a different field name
		printf("  single_cmd[%d]=node=%p content=%p\n", idx, (void*)node, (void*)sc);

		if (!sc)
		{
			printf("    ERROR: single_cmd content is NULL\n");
			return;
		}

		printf("    fdin=%d fdout=%d id=%d builtin=%p redir=%p argv=%p\n",
			sc->fdin, sc->fdout, (int)sc->id, (void*)sc->builtin, (void*)sc->redir, (void*)sc->argv);

		print_argv(sc->argv);

		// If you have a redir printer, call it here; otherwise at least print its pointers.
		// printf("    redir nodes chain head=%p\n", (void*)sc->redir);

		node = node->next; // adjust if your list uses different link field
		idx++;
	}
	if (idx == 100)
		printf("  ... single_cmd log truncated\n");
}


/*******************************another test******************************* */

void	assert_argv_null_terminated(t_single_cmd *sc)
{
	int i = 0;

	if (!sc->argv)
	{
		printf("ERROR: single_cmd argv is NULL (fdin=%d fdout=%d)\n", sc->fdin, sc->fdout);
		return;
	}
	while (sc->argv[i] && i < 1000)
		i++;

	// If it never terminates, you’ll log truncation but you can also bail.
	if (i == 1000)
		printf("ERROR: argv not NULL-terminated within 1000 entries\n");
}
