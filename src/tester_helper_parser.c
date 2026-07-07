#include "../includes/minishell.h"

static void print_argv(char **argv)
{
	int i = 0;
	if (!argv)
	{
		printf("argv=NULL");
		return;
	}
	while (argv[i])
	{
		printf("%s%s", argv[i], argv[i + 1] ? ", " : "");
		i++;
	}
	printf("\n");
}

void print_cmds(t_cmd *cmds, int n)
{
	int i;
	for (i = 0; i < n; i++)
	{
		printf("cmd[%d].argc=%d argv=[", i, cmds[i].argc);
		print_argv(cmds[i].argv);
	}
}

void free_cmds(t_cmd *cmds, int n)
{
	int i;
	if (!cmds) return;
	for (i = 0; i < n; i++)
	{
		// If your t_cmd argv reuses token->text pointers, do NOT free argv[i].
		// Only free the argv array itself (and cmds array).
		free(cmds[i].argv);
	}
	free(cmds);
}
