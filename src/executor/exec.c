/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:52:41 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/18 19:52:26 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include "../../includes/executor.h"
#include <errno.h>

void		end(t_ctx *ctx, t_full_cmd *cmd);
int			apply_all_redir(t_ctx *ctx, t_list_redir *it_redir);
int			exec_bi(t_single_cmd *s_cmd, t_ctx *ctx, t_full_cmd *f_c, int sub);
const char	*ft_strchr(const char *str, char c);
int			find_cmd(char **path, char **argv);
void		check_which_cmd_are_bi(t_list_single_cmd *it_cmd, t_ctx *ctx);
int			ft_lstsize(t_list *lst);
int			evar_lst_to_strs(t_ctx *ctx);
int			extract_path(t_ctx *ctx);

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

static int	run_step(t_ctx *ctx, t_full_cmd *cmd, t_single_cmd *step)
{
	step->id = fork();
	if (step->id < 0)
		return (perror ("err fork in run_step"), 1);
	if (step->id)
		return (0);
	if (step->fdin == -1 || step->fdout == -1)
		exit((end(ctx, cmd), EXIT_FAILURE));
	if (dup2(step->fdin, 0) < 0)
		exit((perror("dup2 fdin=0"), end(ctx, cmd), EXIT_FAILURE));
	if (dup2(step->fdout, 1) < 0)
		exit((perror("dup2 fdout=1"), end(ctx, cmd), EXIT_FAILURE));
	if (close_pipe_ends(cmd))
		exit((end(ctx, cmd), EXIT_FAILURE));
	if (apply_all_redir(ctx, step->redir))
		exit((end(ctx, cmd), EXIT_FAILURE));
	if (step->argv == NULL || step->argv[0] == NULL)
		exit((end(ctx, cmd), EXIT_SUCCESS));
	if (step->builtin)
		exec_bi(step, ctx, cmd, 1);
	if (!ft_strchr(step->argv[0], '/'))
		if (find_cmd(ctx->path, step->argv))
			exit((end(ctx, cmd), 127));
	if (execve(*step->argv, step->argv, ctx->env_strs) < 0)
		exit((perror(*step->argv), end(ctx, cmd), EXIT_FAILURE));
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
	step->fdin = 0;
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
	step->fdout = 1;
	if (run_step(ctx, full_cmd, step))
		return (1);
	return (0);
}

//if (errno == EINTR)
//return 1;// go back to main loop; prompt printed once
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
		{
			if (errno == EINTR)
				return 1;
			return (perror("error waitpid"), 1);
		}
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

	check_which_cmd_are_bi(full_cmd->cmd, ctx);
	if (ft_lstsize(full_cmd->cmd) == 1)
	{
		sole_cmd = full_cmd->cmd->content;
		if (sole_cmd->builtin)
		{
			if (exec_bi(sole_cmd, ctx, full_cmd, 0))
				return (1);
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
