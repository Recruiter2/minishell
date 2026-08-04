/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:11:07 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/04 08:19:17 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../../includes/executor.h"

t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *newelem);
t_list		*ft_lstlast(t_list *lst);
void		put_str_fd(const char *s, int fd);
t_builtin	*is_builtin(char *name, t_list_bi *builtins);

int	add_pipe(t_full_cmd *cmd)
{
	t_single_cmd		*content;
	t_list_single_cmd	*tmp;

	content = malloc (sizeof(*content));
	if (!content)
		return (perror("malloc error"), 1);
	content->redir = NULL;
	content->argv = NULL;
	content->fdin = -1;
	content->fdout = -1;
	tmp = ft_lstnew(content);
	if (!tmp)
		return (1);
	ft_lstadd_back(&cmd->cmd, tmp);
	return (0);
}

t_full_cmd	*initialize_cmd(void)
{
	t_full_cmd	*ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (perror("malloc error"), NULL);
	ret->cmd = NULL;
	add_pipe(ret);
	return (ret);
}

int	add_single_cmd(t_full_cmd *cmd, char **argv)
{
	t_single_cmd		*content;
	t_list_single_cmd	*tmp;

	tmp = ft_lstlast(cmd->cmd);
	content = tmp->content;
	if (content->argv)
		return (put_str_fd("error new cmd without pipe in between\n", 2), 1);
	content->argv = argv;
	return (0);
}

void	check_which_cmd_are_bi(t_list_single_cmd *it_cmd, t_ctx *ctx)
{
	t_single_cmd		*single_cmd;

	while (it_cmd)
	{
		single_cmd = it_cmd->content;
		single_cmd->builtin = is_builtin(*single_cmd->argv, ctx->builtins);
		it_cmd = it_cmd->next;
	}
}
