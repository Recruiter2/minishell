/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signaling.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 16:29:56 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/04 19:28:53 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void sigint_handler(int sig)
{
	(void)sig;
	/* Write newline to move to new line */
	write(1, "\n", 1);
	/* Clear current readline buffer and show prompt again */
	rl_replace_line("", 0);   // replace input line with empty
	rl_on_new_line();		 // move to new line internally
	rl_redisplay();		   // redisplay prompt
}