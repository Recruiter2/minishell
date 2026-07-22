/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:22:09 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/07/22 01:24:15 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// you already have these in your project (from your snippet) 
int is_redir(t_token_type t);

// --------- subfunctions --------- 

static void apply_single_redir(t_full_cmd *full, t_token *op)
{
	//full->redir = full->redir * 1;
	if (!op || !op->next || op->next->type != T_WORD || !op->next->text)
		return ;

	if (op->type == T_REDIR_IN)
		add_file_in(full, op->next->text);
	else if (op->type == T_REDIR_OUT)
		add_file_out(full, op->next->text, 0);
	else if (op->type == T_REDIR_APPEND)
		add_file_out(full, op->next->text, 1);
	else if (op->type == T_HEREDOC)
	{
		// If you have heredoc support in executor, call your heredoc function here.
		   //Placeholder: if your project treats it like input redir, route it: 
		add_file_in(full, op->next->text);
	}
}

static void apply_redirs_from_tokens(t_full_cmd *full, t_token *tokens)
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

static void add_pipeline_cmds_from_segments(t_full_cmd *full, t_token *tokens)
{
	char **res;
	int i;
	char **argv;


	res = build_res_list(tokens);
	if (!res)
		return ;
	i = 0;
	while (res[i])
	{
		//printf("print res[%d] : %s\n", i, res[i]);
		argv = ft_split(res[i], ' ');

		if (argv)
			add_single_cmd(full, argv);
		// free_res(res); //is project-specific; free res[i] + res itself if needed 
		i++;
	}
}

// --------- public dispatcher --------- 

t_full_cmd	*dispatch_lexer_to_full_cmd(t_token *tokens)
{
	t_full_cmd *full;

	full = initialize_cmd();
	if (!full)
		return NULL;

	apply_redirs_from_tokens(full, tokens);
	add_pipeline_cmds_from_segments(full, tokens);

	return full;
}

//*/

/******************debug code or code to do tests******************** */
/*

// you already have these in your project (from your snippet) 
int is_redir(t_token_type t);

// --------- subfunctions --------- 
//
static void apply_single_redir(t_token *op)//t_full_cmd *full, t_token *op)
{
	//full->redir = full->redir * 1;
	if (!op || !op->next || op->next->type != T_WORD || !op->next->text)
		return ;

	if (op->type == T_REDIR_IN)
		printf("add_file_in(full, %s);", op->next->text);//add_file_in(full, op->next->text);
	else if (op->type == T_REDIR_OUT)
		printf("add_file_out(full, %s, 0);", op->next->text);//add_file_out(full, op->next->text, 0);
	else if (op->type == T_REDIR_APPEND)
		printf("add_file_out(full, %s, 1);", op->next->text);//add_file_out(full, op->next->text, 1);
	else if (op->type == T_HEREDOC)
	{
		// If you have heredoc support in executor, call your heredoc function here.
		   //Placeholder: if your project treats it like input redir, route it: 
		printf("add_file_in(full, %s);", op->next->text);//add_file_in(full, op->next->text);
	}
}

static void apply_redirs_from_tokens(t_token *tokens)//t_full_cmd *full, t_token *tokens)
{
	for (t_token *t = tokens; t; t = t->next)
	{
		if (is_redir(t->type))
						printf("apply_single_redir(full, t);");//apply_single_redir(full, t);
	}
}

static void add_pipeline_cmds_from_segments(t_token *tokens)//t_full_cmd *full, t_token *tokens)
{
	char **res;
	int i;
	int j;

	res = build_res_list(tokens);
	if (!res)
		return ;

	i = 0;
	while (res[i])
	{
		char **argv;

		argv = ft_split(res[i], ' ');
		j = 0;
		if (argv)
		{
			printf("add_single_cmd(full, ");
			while (argv[j])
			{
				printf("%s",argv[j]);//add_single_cmd(full, argv);
				j++;
			}
			printf(");");
		}
		// free_res(res); is project-specific; free res[i] + res itself if needed 
		i++;
	}
}

// --------- public dispatcher --------- 

t_full_cmd	*dispatch_lexer_to_full_cmd(t_token *tokens)
{
	t_full_cmd *full;

	full = initialize_cmd();
	if (!full)
		return NULL;

	apply_redirs_from_tokens(tokens);//full, tokens);
	add_pipeline_cmds_from_segments(tokens);//full, tokens);

	return full;
}
//*/