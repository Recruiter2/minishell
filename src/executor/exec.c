/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:52:41 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/30 15:47:45 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "../../includes/prepare_execution.h"

int			apply_redir(t_redir *redir, int *ptr_fd_in, int *ptr_fd_out);
int			find_cmd(char **path, char **argv);
int			ft_lstsize(t_list *lst);
t_builtin	*is_builtin(char *name, t_list_bi *builtins);
void		exec_builtin(t_single_cmd *single_cmd, t_ctx *ctx, t_full_cmd *full_cmd);
int			evar_lst_to_strs(t_ctx *ctx);
int			extract_path(t_ctx *ctx);
void		end(t_ctx *ctx, t_full_cmd *cmd);

static int	prepare_execution(t_ctx *ctx, t_full_cmd *full_cmd)
{
	t_list_redir		*it_redir;
	t_list_single_cmd	*it_cmd;
	t_single_cmd		*single_cmd;

	it_redir = full_cmd->redir;
	while (it_redir)
	{
		if (apply_redir(it_redir->content, &full_cmd->fdin, &full_cmd->fdout))
			return (1);
		it_redir = it_redir->next;
	}
	it_cmd = full_cmd->cmd;
	while (it_cmd)
	{
		single_cmd = it_cmd->content;
		single_cmd->builtin = is_builtin(*single_cmd->argv, ctx->builtins);
		it_cmd = it_cmd->next;
	}
	return (0);
}

static int	close_pipe_ends(t_full_cmd *full_cmd)
{
	t_list_single_cmd	*it_cmd;
	t_single_cmd		*step;

	it_cmd = full_cmd->cmd;
	if (!it_cmd)
		return (0);
	while (it_cmd)
	{
		step = it_cmd->content;
		if (step->fdin > 2)
		{
			if (close(step->fdin))
				return (perror("close fdin in close_pipe_ends"), 1);
		}
		if (step->fdout > 2)
		{
			if (close(step->fdout))
				return (perror("close fdout in close_pipe_ends"), 1);
		}
		it_cmd = it_cmd->next;
	}
	return (0);
}

static int	run_step(t_ctx *ctx, t_full_cmd *full_cmd, t_single_cmd *step)
{
	step->id = fork();
	if (step->id < 0)
		return (perror ("err fork in runstep"), 1);
	if (!step->id)
	{
		if (dup2(step->fdin, 0) < 0)
			exit((perror("dup2 fdin=0"), end(ctx, full_cmd), EXIT_FAILURE));
		if (dup2(step->fdout, 1) < 0)
			exit((perror("dup2 fdout=1"), end(ctx, full_cmd), EXIT_FAILURE));
		if (close_pipe_ends(full_cmd))
			exit((end(ctx, full_cmd), EXIT_FAILURE));
		if (step->builtin)
			exit((exec_builtin(step, ctx, full_cmd), end(ctx, full_cmd), ctx->exit_status));
		find_cmd(ctx->path, step->argv);
		// There is still a problem here
		if (execve(*step->argv, step->argv, ctx->env_strs) < 0)
			exit((perror(*step->argv), end(ctx, full_cmd), EXIT_FAILURE));
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

static int	waits(t_ctx *ctx, t_full_cmd *full_cmd)
{
	t_list_single_cmd	*it_cmd;
	t_single_cmd		*step;
	int					status;

	if (close_pipe_ends(full_cmd))
		return ((end(ctx, full_cmd), 1));
	it_cmd = full_cmd->cmd;
	while (it_cmd)
	{
		step = it_cmd->content;
		if (waitpid(step->id, &status, 0) == -1)
			return (perror("error waitpid"), 1);
		if (WIFEXITED(status))
			ctx->exit_status = WEXITSTATUS(status);
		it_cmd = it_cmd->next;
	}
	return (1);
}

/*
executes the command saved in *full_cmd
*/
int	execute_cmd(t_ctx *ctx, t_full_cmd *full_cmd)
{
	t_single_cmd	*sole_cmd;

	if (prepare_execution(ctx, full_cmd))
		return (1);
	if (ft_lstsize(full_cmd->cmd) == 1)
	{
		sole_cmd = full_cmd->cmd->content;
		if (sole_cmd->builtin)
		{
			exec_builtin(sole_cmd, ctx, full_cmd);
			return (0);
		}
	}
	if (evar_lst_to_strs(ctx))
		return (1);
	if (extract_path(ctx))
		return (1);
	if (start(ctx, full_cmd))
		return (1);
	if (waits(ctx, full_cmd))
		return (1);
	return (0);
}
