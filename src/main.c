/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 21:12:22 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/09 22:27:41 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//static int debug = 0; // toggle for printing raw lines for debugging

	/* Parent: set handlers for interactive prompt */
/* restart interrupted syscalls if appropriate */
	/* Ignore SIGQUIT in parent (Ctrl-\ does nothing) */
/*
int main(void)
{
	
	struct sigaction sa;
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART; 
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	handle_input();
	return 0;
}
*/
	
#include <stdio.h>

/* reuse token_t and lexer() from lexer.c above */

/* helper to show type name */
static const char *type_name(token_type t)
{
	switch (t) {
	case T_WORD: return "WORD";
	case T_PIPE: return "PIPE";
	case T_REDIR_IN: return "REDIR_IN";
	case T_REDIR_OUT: return "REDIR_OUT";
	case T_REDIR_APPEND: return "REDIR_APPEND";
	case T_HEREDOC: return "HEREDOC";
	default: return "UNKNOWN";
	}
}

static void free_tokens(token_t *head)
{
	token_t *p = head;
	while (p) {
		token_t *n = p->next;
		free(p->text);
		free(p);
		p = n;
	}
}
//other
int main(void)
{
	int i;
	token_t *tokens;
	token_t *head_tok;
	const char *tests[] = {
		"echo hello world",
		"echo \"a b\" c",
		"cmd \"\" ''",
		"cat < infile >> outfile",
		"cmd <<'EOF' other",
		"ls -l | grep '^d' ; echo done",
		"echo arg\\ with\\ spaces back\\\\slash",
		"echo \"unclosed",
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
			continue;
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