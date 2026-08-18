/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:29:56 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/18 19:51:29 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
// readline_status is a shared flag between files.
// main sets it to 1 right before calling readline,
// and sets it back to 0 once readline returns.
// The SIGINT handler reads it to know whether it's safe
// to call readline functions (rl_*) and avoid double prompts.
static int readline_status = 0;

	/* Write newline to move to new line */
	/* Clear current readline buffer and show prompt again */
void	sigint_handler(int sig)
{
	(void)sig;
	
	write(1, "\n", 1);
	if (readline_status)
	{
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
// replace input line with empty
	// move to new line internally
			// redisplay prompt

//In forked child, before execve:

//signal(SIGINT, SIG_DFL);
//signal(SIGQUIT, SIG_DFL);
