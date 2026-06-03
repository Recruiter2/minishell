/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:12:22 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/03 21:55:49 by tzinaliy         ###   ########.fr       */
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

//static int debug = 0; // toggle for printing raw lines for debugging

// return 1 if line is all whitespace or empty
static int is_blank(const char *s)
{
	while (*s)
	{
		if (!ft_isspace((unsigned char)*s))
			return 0;
		s++;
	}
	return 1;
}

// Add a line to history (call after checking not blank)
/* Optionally keep your own persistent history array/file in this function */
static void add_shell_history(const char *line)
{
	if (!line || *line == '\0')
		return;
	add_history(line);

}

// Print history builtin: "history"
// start index at 1 to match bash
static void builtin_history(void)
{
	HIST_ENTRY **hist_list = history_list();
	if (!hist_list) {
		return;
	}
	for (int i = 0; hist_list[i] != NULL; ++i) {
		printf("%4d  %s\n", i + history_base, hist_list[i]->line);
	}
}

int main(void)
{
	char *line;
	int all_blank = 1;
	int	i;

	i = 0;
	while (1) {
		line = readline("minishell$ ");
		while (line[i])
		{
			if (!ft_isspace(line[i]))
			{
				all_blank = 0;
				break;
			}
			i++;
		}
		if (!all_blank) {
			add_shell_history(line);
			if (strcmp(line, "history") == 0)
				builtin_history();
		}
		if (!line)
		{
			write(1, "\n", 1);
			break;
		}
		if (is_blank(line))
		{
			free(line);
			continue;
		}
		free(line);
	}
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