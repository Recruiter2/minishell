/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:48:35 by marhuber          #+#    #+#             */
/*   Updated: 2026/06/06 17:34:55 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../executor.h"

int	read_envp(char **envp, t_ctx *ctx);
int	execute(t_ctx *ctx, t_fullcmd *fullcmd);
char	**ft_split(char const *s, char c);


int	main(int argc, char **argv, char **envp)
{
	t_ctx ctx;
	t_fullcmd fullcmd;
	char** argvvv[2];

	argc = 0;
	argc++;
	**argv = 0;
	if (read_envp(envp, &ctx))
		return (1);
	argvvv[0] = ft_split("ls -a", ' ');
	argvvv[1] = NULL;
	fullcmd.cmds = argvvv;

	execute(&ctx, &fullcmd);
}