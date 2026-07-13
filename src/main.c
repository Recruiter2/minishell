/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:12:22 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/07/13 17:23:28 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//static int debug = 0; // toggle for printing raw lines for debugging

	/* Parent: set handlers for interactive prompt */
/* restart interrupted syscalls if appropriate */
	/* Ignore SIGQUIT in parent (Ctrl-\ does nothing) */
/*
int main(int argc, char **argv, char **envp)
{
	//the commented out line are here for signal hanling
	/*struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; 
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);//*/
	handle_input();
	return 0;
}
//*/
	
#include <stdio.h>

/* reuse t_token	and lexer() from lexer.c above */

/* helper to show type name */
/*static const char	*type_name(t_token_type t)
{
	switch (t)
	{
	case	T_WORD: return "WORD";
	case	T_PIPE: return "PIPE";
	case	T_REDIR_IN: return "REDIR_IN";
	case	T_REDIR_OUT: return "REDIR_OUT";
	case	T_REDIR_APPEND: return "REDIR_APPEND";
	case	T_HEREDOC: return "HEREDOC";
	default: return "UNKNOWN";
	}
}//*/

//it seems this function was written twice check in lexer.... however this is test section so it will be deleted
/*static void	free_tokens(t_token	*head)
{
	t_token	*p = head;
	while (p) {
		t_token	*n = p->next;
		free(p->text);
		free(p);
		p = n;
	}
}//*/




//tests for argument concat (failed btw or not)
/*
int main(void)
{
	int     i;
	t_token *tokens;
	//t_token *head_tok;

	char *tests[] = {
		"cat < in.txt | wc -l",
		"echo \"a b\" c",
		"cmd \"\" ''",
		"cat < infile >> outfile",
		"cmd <<'EOF' other",
		"ls -l | grep '^d' ",
		"echo arg with spaces backslash",
		"echo \"unclosed",
		"a\"|<>\"b",
		"cat < in.txt | wc -l",
		"< txt.txt grep et | wc -l > out.txt",
		NULL
	};

	for (i = 0; tests[i]; i++)
	{
		printf("=== test %d: %s\n", i, tests[i]);

		// this MUST match your working call style 
		tokens = lexer(tests[i]);
		if (!tokens)
		{
			printf("lexer returned NULL\n\n");
			continue;
		}
		dispatch_lexer_to_full_cmd(tokens);

		//char **res = build_res_list(tokens);

		// Print res for now (so you can see if grouping matches).
		//printf("res: ");
		//for (int k = 0; res && res[k]; k++)
		//	printf("\"%s\" ", res[k]);
		//printf("\n\n");

		// free both 
		// free_res(res);  // if you have it 
		//free_tokens(tokens);
		//
	//}
	return 0;
}
//*/

//tests for token
/*
int	main(void)
{
	int		i;
	t_token	*tokens;
	t_token	*head_tok;
	char	*tests[] =
	{
		"echo \"hello world\"",
		"echo \"a b\" c",
		"cmd \"\" ''",
		"cat < infile >> outfile",
		"cmd <<'EOF' other",
		"ls -l | grep '^d' ",
		"echo arg with spaces backslash",
		"echo \"unclosed",
		"a\"|<>\"b",
		"cat < in.txt | wc -l",
		"< txt.txt grep et | wc -l > out.txt",
		NULL
	};

	i = 0;
	while (tests[i] != NULL)
	{
		ft_printf("=== test %d: %s\n", i, tests[i]);
		tokens = lexer(tests[i]);
		i++;
		if (!tokens)
		{
			printf("lexer returned NULL (syntax error / OOM)\n\n");
			continue ;
		}
		head_tok = tokens;
		while (head_tok)
		{
			ft_printf("%s ", type_name(head_tok->type));
			if (head_tok->text)
				printf("\"%s\" ", head_tok->text);
			else
				printf("<op> ");
			printf("quote=%c\n", head_tok->quote ? head_tok->quote : '0');
			head_tok = head_tok->next;
		}
		free_tokens(tokens);
		printf("\n");
	}
	return 0;
}
//*/
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