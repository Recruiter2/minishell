/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:55:51 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/04 14:32:05 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// return 1 if line is all whitespace or empty
int is_blank(const char *s)
{
	while (*s)
	{
		if (!ft_isspace((unsigned char)*s))
			return 0;
		s++;
	}
	return 1;
}

void	handle_input(void)
{
	char *line;
	int all_blank;

	while (1) {
		line = readline("minishell$ ");
		all_blank = is_blank(line);
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
		free(line);
	}
}