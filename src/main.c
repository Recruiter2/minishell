/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:12:22 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/02 22:09:43 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// File: main.c
// Compile with: gcc -Wall -Wextra -Werror main.c -lreadline
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h>
#include "../Libft/libft.h"

static int debug = 0; // toggle for printing raw lines for debugging

// return 1 if line is all whitespace or empty
static int is_blank(const char *s)
{
	while (*s)
	{
		if (!isspace((unsigned char)*s))
			return 0;
		s++;
	}
	return 1;
}

int main(void)
{
	char *line;

	while (1) {
		line = readline("minishell$ "); // prompt (replace with desired prompt)
		if (!line)
		{					// EOF (Ctrl-D)
			write(1, "\n", 1);		  // mimic bash newline on EOF
			break;
		}

		if (*line) 
			add_history(line);   // add non-empty lines to forbidden history; in fact we are using external history 🤡 we are supposed to code it ourselves

		if (is_blank(line))
		{		   // ignore empty / whitespace-only lines
			free(line);
			continue; //is continue even allowed?
		}

		if (debug)
		{					// optional debug output
			printf("[DEBUG] raw input: %s\n", line);
		}

		// Here you would:
		// 1) lex/tokenize the line
		// 2) parse into commands & redirections
		// 3) expand variables, handle quotes
		// 4) execute commands (builtins inline, others via fork+execve)
		//
		// If execution fails because command not found, print:
		//   minishell: <cmd>: command not found
		//
		// Do not automatically print "command not found" here without attempting exec.

		free(line);
	}

	return 0;
}
