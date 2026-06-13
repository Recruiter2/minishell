/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:48:35 by marhuber          #+#    #+#             */
/*   Updated: 2026/06/13 14:53:12 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"
#include <stdio.h>
#include <stdlib.h>

int	read_envp(char **envp, t_ctx *ctx);
int	execute(t_ctx *ctx, t_fullcmd *fullcmd);
char	**ft_split(char const *s, char c);
void	free_all(char ***strs);


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

	argc = 0;
	argc++;
	**argv = 0;
	if (read_envp(envp, &ctx))
		return (1);
	fullcmd.cmds = malloc(sizeof(*fullcmd.cmds) * 3);
	// first run wit: < txt.txt grep et | wc -l > out.txt
	fullcmd.cmds[0] = ft_split("grep et", ' ');
	fullcmd.cmds[1] = ft_split("wc -l", ' ');
	fullcmd.cmds[2] = NULL;
	fullcmd.namefilein = "txt.txt";
	fullcmd.namefileout = "out.txt";
	fullcmd.fileout_append = 0;
	execute(&ctx, &fullcmd);
	free_all(fullcmd.cmds);
	free_all(fullcmd.cmds + 1);
	// second run with: < txt.txt grep sit | wc -l > out.txt
	fullcmd.cmds[0] = ft_split("grep laoreet", ' ');
	fullcmd.cmds[1] = ft_split("wc -l", ' ');
	fullcmd.fileout_append = 1;
	execute(&ctx, &fullcmd);
	free_all(fullcmd.cmds);
	free_all(fullcmd.cmds + 1);
	// second run with: << END grep I | wc -l >> out.txt
	fullcmd.cmds[0] = ft_split("grep I", ' ');
	fullcmd.cmds[1] = ft_split("wc -l", ' ');
	fullcmd.namefilein = 0;
	fullcmd.heredocdelim = "END";
	execute(&ctx, &fullcmd);
	free_all(fullcmd.cmds);
	free_all(fullcmd.cmds + 1);
	// finish clean up
	free(fullcmd.cmds);
	free_all(&ctx.path);
}