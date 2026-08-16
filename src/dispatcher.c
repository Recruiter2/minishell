/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/13 14:22:09 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/16 15:35:32 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	chek_word_piplin(t_full_cmd *full, t_token *t, \
t_ctx *ctx, char ***argv);
int		consume_word_to_argv(t_token **t, char ***argv, t_ctx *ctx);

// --------- subfunctions --------- 
//building the cmd (made out of linked list) that will be send to executor

// explicit boundary node 			add_pipe(full);
// put after free_res(res);
//is project-specific; free res[i] + res itself if needed 
//if (!consume_word_to_argv could add in if 	// free_argv(&argv);

// Create a node for this segment
//add_pipe(full);
// If argv is empty, you may want to remove the node or allow it,
// but the current executor likely expects no empty commands.
int pipeline_from_tokens(t_full_cmd *full, t_token *tokens, t_ctx *ctx)
{
    t_token *t = tokens;
    char **argv = NULL;

	//printf("pipeline_from_tokens: start t=%p\n", (void*)tokens);
    if (!chek_word_piplin(full, t, ctx, &argv)) //error
        return 0;

    if (argv && argv[0])
    {
		//printf("pipeline_from_tokens: about to add_pipe/full->cmd=%p\n", (void*)full->cmd);
        //add_pipe(full);          // rename later if you want; it just means "add a simple cmd node"
		//printf("pipeline_from_tokens: argv=%p argv[0]=%s\n",
       //(void*)argv, (argv && argv[0]) ? argv[0] : "(null)");
        add_single_cmd(full, argv);
    }
    // else: no words in this segment => do not add a node
	return 1;
}



// ownership passes to the command node
	//if (argv && *argv && (*argv)[0])
// IMPORTANT: detach from builder so next argv_build allocates anew
	//add_single_cmd(full, *argv);
	//*argv = NULL;//shouldn't we free agrv? nope we free it in the end smh smh
int chek_word_piplin(t_full_cmd *full, t_token *t, t_ctx *ctx, char ***argv)
{
    while (t && t->type != T_PIPE)
    {
        if (t->type == T_WORD)
        {
            if (!consume_word_to_argv(&t, argv, ctx))
                return 0;
            continue;
        }
        if (is_redir(t->type))
        {
            if (!consume_redir(full, &t))
				return 0; //stop whole line parsing
            continue;
        }
        t = t->next;
    }
    return 1;
}

//*/

/*
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
				return ;
			continue ;
		}
		if (t->type == T_PIPE)
		{
			if (argv)
				add_single_cmd(full, argv);
			add_pipe(full);
			argv = NULL;
			t = t->next;
			continue ;
		}
		if (is_redir(t->type))
		{
			consume_redir(full, &t);
			continue ;
		}
		t = t->next;
	}
	if (argv)
		add_single_cmd(full, argv);
}
//*/
// --------- public dispatcher --------- 
// it seeems the idea here is we iterate through tokens to build a whole pipe
// t->word t->word t->word until it's t->pipe
// the last one  was supposed to be 	pipeline_from_tokens(full, tokens, ctx);
// for the purpose of the last token after the pipe so it's not left unprocessed
/*void	dispatch_to_full_cmd(t_token *tokens, t_full_cmd *full, t_ctx *ctx)
{
	t_token		*iterator;
	t_token		*next_chunk;

	iterator = tokens;
	while (iterator->next != NULL) //error most likely deadly
	{
		if (iterator->next->type == T_PIPE)
		{
			next_chunk = iterator->next->next;
			iterator->next = NULL;
			pipeline_from_tokens(full, tokens, ctx);
			add_pipe(full);
			iterator = next_chunk;
			tokens = next_chunk;
		}
		else
			iterator = iterator->next;
	}
	pipeline_from_tokens(full, tokens, ctx);
	return ;
}
//*/
//added safety
//pipeline_from_tokens(full, t, ctx);build a segment starting at `t`
//while (it && it->type != T_PIPE) jump `t` to the token right after the next pipe
int dispatch_to_full_cmd(t_token *tokens, t_full_cmd *full, t_ctx *ctx)
{
    t_token *t = tokens;

    if (!tokens || !full)
        return 0;

    while (t)
    {
        // Skip leading pipes to avoid creating empty “nodes” (optional)
        while (t && t->type == T_PIPE)
            t = t->next;
        if (!t)
            break;
    add_pipe(full);
        // Build one segment up to the next pipe
		//printf("dispatch: token ptr=%p type=%u\n",
       //(void*)t, t ? (unsigned)t->type : 0u);
        if (!pipeline_from_tokens(full, t, ctx))
			return 0;//error

        // Advance t to the token after the next pipe
        while (t && t->type != T_PIPE)
            t = t->next;
        if (t && t->type == T_PIPE)
            t = t->next;
    }
	return 1;
}
