/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:55:51 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/04 15:27:36 by marhuber         ###   ########.fr       */
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

int	run_line(t_ctx *ctx, char *line)
{
	t_token		*tokens;
	t_full_cmd	*cmd;

	if (!line || is_blank(line))
		return (0);
	add_shell_history(line);
	if (ft_strncmp(line, "history", 7) == 0)
		return (builtin_history(), 0);
	tokens = lexer(line);
	if (!tokens)
		return (1);
	cmd = initialize_cmd();
	if (!cmd)
		return (1);
	dispatch_to_full_cmd(tokens, cmd, ctx);
	if (cmd)
	{
		cmd->tokens = tokens;
		execute_cmd(ctx, cmd);
		destroy_full_cmd(&cmd);
	}
	return (0);
}
