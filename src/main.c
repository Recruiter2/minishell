/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:12:22 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/04 14:32:09 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//static int debug = 0; // toggle for printing raw lines for debugging

int main(void)
{
	handle_input();
	return 0;
}

/* tools to work with later on and functionality we 'd like to add
if (debug)
		{					// optional debug output
			printf("[DEBUG] raw input: %s\n", line);
		}

		Here you would:
		1) lex/tokenize the line
		2) parse into commands & redirections
		3) expand variables, handle quotes
		4) execute commands (builtins inline, others via fork+execve)

		If execution fails because command not found, print:
		minishell: <cmd>: command not found
		
		Do not automatically print "command not found" here without attempting exec.

*/