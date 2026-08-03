/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:22:09 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/03 22:04:04 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// you already have these in your project (from your snippet) 
int is_redir(t_token_type t);

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
		add_file_in(full, op->next->text);
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
void	pipeline_from_seg(t_full_cmd *full, t_token *tokens, t_ctx *ctx)
{
	char	**res;
	int		i;
	char	**argv;

	res = build_res_list(tokens, ctx);
	if (!res)
		return ;
	i = 0;
	while (res[i])
	{
		argv = ft_split(res[i], ' ');
		if (argv)
			add_single_cmd(full, argv);
		if (res[i + 1])
			add_pipe(full);
		i++;
	}
}

// --------- public dispatcher --------- 

t_full_cmd	*dispatch_lexer_to_full_cmd(t_token *tokens, t_ctx *ctx)
{
	t_full_cmd *full;

	full = initialize_cmd();
	if (!full)
		return NULL;
	apply_redirs_from_tokens(full, tokens);
	pipeline_from_seg(full, tokens, ctx);
	return (full);
}
