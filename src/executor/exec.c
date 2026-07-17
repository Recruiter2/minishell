/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:52:41 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/17 16:33:31 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <sys/wait.h>

int		prepare_redir(t_redir *redir, int *ptr_fd_in, int *ptr_fd_out);
int		find_cmd(char **path, char **argv);
void	end(t_ctx *ctx, t_full_cmd *cmd);

static int	close_pipes_before(t_full_cmd *full_cmd, t_single_cmd *this_cmd)
{
	t_list_single_cmd	*it_step;
	t_single_cmd		*earlier_cmd;

	it_step = full_cmd->cmd;
	while (it_step->content != this_cmd)
	{
		earlier_cmd = it_step->content;
		if (close(earlier_cmd->fdout))
			return (1);
		it_step = it_step->next;
	}
	return (0);
}

static int	run_step(t_ctx *ctx, t_full_cmd *full_cmd, t_single_cmd *this_cmd)
{
	this_cmd->id = fork();
	if (this_cmd->id < 0)
		return (perror ("err fork in runstep"), 1);
	if (!this_cmd->id)
	{
		if (close_pipes_before(full_cmd, this_cmd))
			exit((end(ctx, full_cmd), EXIT_FAILURE));
		if (dup2(this_cmd->fdin, 0) < 0)
			exit((perror("dup2 fdin=0"), end(ctx, full_cmd), EXIT_FAILURE));
		if (dup2(this_cmd->fdout, 1) < 0)
			exit((perror("dup2 fdout=1"), end(ctx, full_cmd), EXIT_FAILURE));
		find_cmd(ctx->path, this_cmd->argv);
		if (execve(*this_cmd->argv, this_cmd->argv, ctx->envp) < 0)
			exit((perror("execve"), end(ctx, full_cmd), EXIT_FAILURE));
	}
	return (0);
}

static int	start(t_ctx *ctx, t_full_cmd *full_cmd)
{
	t_list_single_cmd	*it_cmd;
	t_single_cmd		*step;
	int					pipedes[2];

	it_cmd = full_cmd->cmd;
	if (!it_cmd)
		return (0);
	step = it_cmd->content;
	step->fdin = full_cmd->fdin;
	while (it_cmd->next)
	{
		if (pipe(pipedes))
			return (perror("error pipe"), 1);
		step->fdout = pipedes[1];
		if (run_step(ctx, full_cmd, step))
			return (1);
		it_cmd = it_cmd->next;
		step = it_cmd->content;
		step->fdin = pipedes[0];
	}
	step->fdout = full_cmd->fdout;
	if (run_step(ctx, full_cmd, step))
		return (1);
	return (0);
}

static void	waits(t_list_single_cmd *it_cmd)
{
	t_single_cmd		*step;

	while (it_cmd)
	{
		step = it_cmd->content;
		waitpid(step->id, 0, 0);
		if (-1 < step->fdin)
			close(step->fdin);
		if (-1 < step->fdout)
			close(step->fdout);
		it_cmd = it_cmd->next;
	}
}

/*
executes the command saved in *full_cmd
*/
int	execute_cmd(t_ctx *ctx, t_full_cmd *full_cmd)
{
	t_list_redir	*it_redir;

	it_redir = full_cmd->redir;
	while (it_redir)
	{
		prepare_redir(it_redir->content, &full_cmd->fdin, &full_cmd->fdout);
		it_redir = it_redir->next;
	}
	if (start(ctx, full_cmd))
		return (1);
	waits(full_cmd->cmd);
	return (0);
}
