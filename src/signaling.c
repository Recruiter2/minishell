/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:29:56 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/05 12:18:38 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

	/* Write newline to move to new line */
	/* Clear current readline buffer and show prompt again */

void sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0); 
	rl_on_new_line();
	rl_redisplay();
}
// replace input line with empty
	// move to new line internally
			// redisplay prompt

//In forked child, before execve:

//signal(SIGINT, SIG_DFL);
//signal(SIGQUIT, SIG_DFL);