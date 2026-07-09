#include "../includes/minishell.h"

t_full_cmd	*initialize_cmd(void)
{
	t_full_cmd	*ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL); // perror?
	ret->redir = NULL;
	ret->cmd = NULL;
	return (ret);
}