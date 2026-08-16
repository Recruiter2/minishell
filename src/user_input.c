/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:55:51 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/16 15:33:07 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_full_cmd(t_full_cmd *cmd);
void	assert_argv_null_terminated(t_single_cmd *sc);


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
	tokens = lexer(line);//error
	if (!tokens)
		return (free_tokens_list(tokens), 1);
	cmd = initialize_cmd();
	if (!cmd)
		return (free_tokens_list(tokens), destroy_full_cmd(&cmd), 1);
	if (!dispatch_to_full_cmd(tokens, cmd, ctx))
	{
		destroy_full_cmd(&cmd);
		free_tokens_list(tokens);
		return 0;
	}

	if (cmd)
	{
		cmd->tokens = tokens;
		//print_full_cmd(cmd);
		/*// this part was most likely for debug we will remove it
		t_list_single_cmd *n = cmd->cmd;
while (n)
{
	t_single_cmd *sc = n->content;
	if (!sc)
	{
		printf("ERROR: single_cmd content NULL\n");
		break;
	}
	if (sc->argv == NULL && sc->builtin == NULL)
	{
		printf("ERROR: empty command node: argv=NULL builtin=NULL (sc=%p)\n", (void*)sc);
	}
	n = n->next;
}
		printf("EXECUTE_CMD REACHED\n");
*/
		execute_cmd(ctx, cmd);
		destroy_full_cmd(&cmd);
	}
	return (0);
}

/*


int	run_line(t_ctx *ctx, char *line)
{
	t_token		*tokens;
	t_full_cmd	*cmd;

	if (!line || is_blank(line))
		return (0);
	add_shell_history(line);
	if (ft_strncmp(line, "history", 7) == 0)
		return (builtin_history(), 0);
	tokens = lexer(line);//error
	if (!tokens)
		return (free_tokens_list(tokens), 1);
	cmd = initialize_cmd();
	if (!cmd)
	{
		free_tokens_list(tokens);
		destroy_full_cmd(&cmd);
		return (1);
	}
	dispatch_to_full_cmd(tokens, cmd, ctx);

	if (cmd)
	{
		cmd->tokens = tokens;
		print_full_cmd(cmd);

		int invalid = 0;
		t_list_single_cmd *n = cmd->cmd;
		while (n)
		{
			t_single_cmd *sc = n->content;
			if (!sc)
			{
				invalid = 1;
				break;
			}

			// for your case: redirection-only => syntax error
			if (sc->argv == NULL && sc->builtin == NULL)
			{
				printf("ERROR: empty command node: argv=NULL builtin=NULL (sc=%p)\n", (void*)sc);
				invalid = 1;
				break;
			}
			n = n->next;
		}

		if (invalid)
		{
			destroy_full_cmd(&cmd);
			return (2); // pick your project's syntax-error code
		}
		printf("EXECUTE_CMD REACHED\n");
		execute_cmd(ctx, cmd);
		destroy_full_cmd(&cmd);
	}
	return (0);
}
*/