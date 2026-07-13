/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:55:51 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/07/13 15:49:00 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// return 1 if line is all whitespace or empty
int	is_blank(const char *s)
{
	while (*s)
	{
		if (!ft_isspace((unsigned char)*s))
			return (0);
		s++;
	}
	return (1);
}

void	handle_input(void)
{
	char	*line;
	t_token	*tokens;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		if (!is_blank(line))
		{
			add_shell_history(line);
			tokens = lexer(line);
			if (tokens)
				dispatch_lexer_to_full_cmd(tokens);
			else
			{
// lexer returned NULL -> usually means parse error / invalid quotes // do nothing here unless your project requires a specific error print
			}
		}
		free(line);
	}
}

/*
//history command is not needed so we won't further improve it to handle spaces
void	handle_input(void)
{
	char	*line;
	int		all_blank;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			write(1, "\n", 1);
			break ;
		}
		all_blank = is_blank(line);
		if (!all_blank)
		{
			add_shell_history(line);
			if (ft_strncmp(line, "history", 7) == 0)
				builtin_history();
		}
		free(line);
	}
}
//*/
