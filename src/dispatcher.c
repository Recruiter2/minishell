/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:22:09 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/07 16:03:41 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		consume_word_to_argv(t_token **t, char ***argv, t_ctx *ctx);
void	free_all(char ***strs);

// --------- subfunctions --------- 
//building the cmd (made out of linked list) that will be send to executor
void	apply_single_redir(t_full_cmd *full, t_token *op)
{
	if (!op || !op->next || op->next->type != T_WORD || !op->next->text)
		return ;
	if (op->type == T_REDIR_IN)
		add_file_in(full, op->next->text);
	else if (op->type == T_REDIR_OUT)
		add_file_out(full, op->next->text, 0);
	else if (op->type == T_REDIR_APPEND)
		add_file_out(full, op->next->text, 1);
	else if (op->type == T_HEREDOC)
		add_here_doc(full, op->next->text);
}

void	apply_redirs_from_tokens(t_full_cmd *full, t_token *tokens)
{
	t_token	*t;

	t = tokens;
	while (t)
	{
		if (is_redir(t->type))
			apply_single_redir(full, t);
		t = t->next;
	}
}

// explicit boundary node 			add_pipe(full);
// put after free_res(res);
//is project-specific; free res[i] + res itself if needed 
void	pipeline_from_tokens(t_full_cmd *full, t_token *tokens, t_ctx *ctx)
{
	t_token	*t;
	char	**argv;

	t = tokens;
	argv = NULL;

	while (t)
	{
		if (t->type == T_WORD)
		{
			if (!consume_word_to_argv(&t, &argv, ctx))
			{
				// free_argv_if_needed(&argv);
				return;
			}
			continue;
		}
		if (t->type == T_PIPE)
		{
			if (argv)
				add_single_cmd(full, argv);
			add_pipe(full);
			argv = NULL;
			t = t->next;
			continue;
		}
		if (is_redir(t->type))
		{
			consume_redir(&t); // keep your existing behavior
			continue;
		}
		t = t->next;
	}

	if (argv)
		add_single_cmd(full, argv);
}

// --------- public dispatcher --------- 

void	dispatch_to_full_cmd(t_token *tokens, t_full_cmd *full, t_ctx *ctx)
{
	t_token		*iterator;
	t_token		*next_chunk;

	iterator = tokens;
	while (iterator->next != NULL)
	{
		if (iterator->next->type == T_PIPE)
		{
			next_chunk = iterator->next->next;
			iterator->next = NULL;
			apply_redirs_from_tokens(full, tokens);
			pipeline_from_tokens(full, tokens, ctx);
			add_pipe(full);
			iterator = next_chunk;
			tokens = next_chunk;
		}
		else
			iterator = iterator->next;
	}
	apply_redirs_from_tokens(full, tokens);
	pipeline_from_tokens(full, tokens, ctx);
	return ;
}
