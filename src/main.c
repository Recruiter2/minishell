/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:12:22 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/18 19:51:45 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <unistd.h>
static int readline_status;
 // declaration

/// signal(SIGQUIT, SIG_IGN);  // Ignore SIGQUIT in the shell
// sa signal action
static int	setup_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	if (sigaction(SIGINT, &sa, NULL) == -1)
		return (1);
	if (signal(SIGQUIT, SIG_IGN) == SIG_ERR)
		return (1);
	return (0);
}

// ft_putendl_fd writes to fd 2 and return an int to ignore or use
//function to handle args example ./minishell args
//but this is not asked 
static int	arg_error(void)
{
	ft_putendl_fd("can't execute binary", 2);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_ctx		ctx;
	char		*line;


	if (argc != 1)
		return (arg_error());
	(void)argv;
	if (init_ctx(&ctx, envp))
		return (1);
	if (setup_signals())
		return (1);
	while (1)
	{
		readline_status = 1;
		line = readline("minishell$ ");
		readline_status = 0;
		if (!line)
		{
			//write(1, "\n", 1);
			break ;
		}
		
		run_line(&ctx, line);
		free(line);
	}
	free_ctx_ressources(&ctx);
	return (0);
}
