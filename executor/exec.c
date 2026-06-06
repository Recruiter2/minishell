/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:52:41 by marhuber          #+#    #+#             */
/*   Updated: 2026/06/06 17:01:22 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include "executor.h"

char	*ft_strjoin(char const *s1, char const *s2);

int	find_cmd(char **path, char **argv)
{
	char	*tmp;

	if (access(*argv, F_OK))
	{
		while (*path)
		{
			tmp = ft_strjoin(*path, *argv);
			if (!tmp)
				return (1);
			if (access(tmp, F_OK))
			{
				free(tmp);
				path++;
			}
			else
			{
				free(*argv);
				*argv = tmp;
				return (0);
			}
		}
	}
	return (0);
}

static int	openfiles(t_fullcmd *fullcmd, t_step *stepcol, int n)
{
	int	o_flag_out;

	if (fullcmd->namefilein == NULL)
		stepcol[0].fdin = 0;
	else 
	{
		stepcol[0].fdin = open(fullcmd->namefilein, O_RDONLY);
		if (stepcol[0].fdin < 0)
			return (perror(fullcmd->namefilein), 1);
	}
	if (fullcmd->namefileout == NULL)
		stepcol[n - 1].fdout = 1;
	else
	{
		if (1)
			o_flag_out = O_WRONLY | O_CREAT | O_APPEND;
		else
			o_flag_out = O_WRONLY | O_CREAT | O_TRUNC;
		stepcol[n - 1].fdout = open(fullcmd->namefileout, o_flag_out, 0664);
		if (stepcol[n - 1].fdout < 0)
			return (perror(fullcmd->namefileout), 1);
	}
	return (0);
}

void	end(t_ctx *ctx)
{
	ctx++;
}

static int	run_a_step(t_ctx *ctx, t_step *stepcol, t_step *current_step, t_singlecmd argv)
{
	t_step	*it_step;

	current_step->id = fork();
	if (current_step->id < 0)
		return (perror ("err fork in runstep"), 1);
	if (!current_step->id)
	{
		it_step = stepcol;
		while (it_step < current_step)
			close(it_step++->fdout);
		if (dup2(current_step->fdin, 0) < 0)
			exit((perror("err dup2 fdin = 0"), end(ctx), EXIT_FAILURE));
		if (dup2(current_step->fdout, 1) < 0)
			exit((perror("err dup2 fdout = 1"), end(ctx), EXIT_FAILURE));
		if (execve(*argv, argv, ctx->envp) < 0)
			exit((perror("err execve in runstep"), end(ctx), EXIT_FAILURE));
	}
	return (0);
}

int start(t_ctx *ctx, t_fullcmd *fullcmd, t_step *stepcol, int n)
{
	t_singlecmd	*it_cmd;
	t_step	*it_step;
	int		pipedes[2];
	int		i;

	it_cmd = fullcmd->cmds;
	it_step = stepcol;
	i = n - 1;
	while (i--)
	{
		if (pipe(pipedes))
			return (perror("error pipe"), 1);
		it_step->fdout = pipedes[1];
		if (run_a_step(ctx, stepcol, it_step, *it_cmd))
			return (1);
		it_step++;
		it_step->fdin = pipedes[0];
		it_cmd++;
	}
	if (run_a_step(ctx, stepcol, it_step, *it_cmd))
		return (1);
	
return (0);
}


static void	waits(t_step *stepcol, int n)
{
	t_step	*it_step;
	int		i;

	it_step = stepcol;
	i = n;
	while (i--)
	{
		waitpid(it_step->id, 0, 0);
		if (-1 < it_step->fdin)
			close(it_step->fdin);
		if (-1 < it_step->fdout)
			close(it_step->fdout);
		it_step++;
	}
}


/*
executes the command saved in *fullcmd

(frees ?)
*/
int	execute(t_ctx *ctx, t_fullcmd *fullcmd)
{
	t_step		*stepcol;
	t_singlecmd	*it_cmd;
	int			n;

	it_cmd = fullcmd->cmds;
	n = 0;
	while(it_cmd)
	{
		if (find_cmd(ctx->path, *it_cmd))
			return (1);
		it_cmd++;
		n++;
	}
	stepcol = malloc(sizeof(*stepcol) * n);
	if (!stepcol)
		return (perror("malloc error"), 1);
	if (openfiles(fullcmd, stepcol, n))
		return (1);
	if (start(ctx, fullcmd, stepcol, n))
		return (1);
	waits(stepcol, n);
	return (0);
}