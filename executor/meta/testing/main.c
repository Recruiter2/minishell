/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:48:35 by marhuber          #+#    #+#             */
/*   Updated: 2026/06/07 20:40:26 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"
#include <stdio.h>
#include <stdlib.h>

int	read_envp(char **envp, t_ctx *ctx);
int	execute(t_ctx *ctx, t_fullcmd *fullcmd);
char	**ft_split(char const *s, char c);

void print_single_cmd(t_singlecmd singlecmd)
{
	while (*singlecmd)
	{
		printf("%s\n", *singlecmd);
		singlecmd++;
	}
	printf("-\n");
}

void print_cmds(t_singlecmd *cmds)
{
	while (*cmds)
		print_single_cmd(*cmds++);
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx ctx;
	t_fullcmd fullcmd;
	t_singlecmd	*mycmds;

	argc = 0;
	argc++;
	**argv = 0;
	if (read_envp(envp, &ctx))
		return (1);
	mycmds = malloc(sizeof(*mycmds) * 3);
	mycmds[0] = ft_split("grep et", ' ');
	mycmds[1] = ft_split("wc -l", ' ');
	mycmds[2] = NULL;
	fullcmd.cmds = mycmds;
	fullcmd.namefilein = "txt.txt";
	fullcmd.namefileout = "out.txt";
	// print_cmds(mycmds);
	execute(&ctx, &fullcmd);
}