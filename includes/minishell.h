/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:29:04 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/07/22 01:12:30 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

//include executor
#include "get_next_line.h"
#include "executor.h"
#include "environment.h"
#include "prepare_execution.h"
typedef enum e_token
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
}	t_token_type;
// <
// >
// >>
// <<

// raw text (without surrounding quotes)
// 0 = none, '\'' or '"' if entire token was quoted


typedef struct s_token
{
	t_token_type	type;
	char			*text;
	char			quote;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
    char **argv;  // NULL-terminated: argv[0] is program, argv[1...] are args
    int    argc;   // optional helper
    // optionally you’ll also store redirections/fds info here
} t_cmd;



//test from executor struct
/*
typedef struct s_redirection
{
	int		is_input;
	int		is_here_doc;
	int		append_mode;
	char	*name;
}			t_redir;
//
//
 //This is an element within a list of redirections
 //@param content points at an instance of t_redir
//
typedef t_list	t_list_redir;

typedef struct s_simple_cmd
{
	char	**argv;
	int		fdin;
	int		fdout;
	pid_t	id;
}			t_single_cmd;

typedef t_list	t_list_single_cmd;
typedef struct s_full_command
{
	t_list_redir		*redir;
	t_list_single_cmd	*cmd;
	int					fdin;
	int					fdout;
}						t_full_cmd;
//*/
char	**ft_split(char const *s, char c);

//end of test from executor struct

//function for user input or parsing...
// this function check if readline is empty
int		is_blank(const char *s);
void	handle_input(void);

// history functions
void	add_shell_history(const char *line);
void	builtin_history(void);

// signaling
void	sigint_handler(int sig);

//lexer

t_token	*lexer(char *s);
void	free_tokens(t_token	*head);


t_token	*tok_new(t_token_type type, char *text, char quote);
int		consume_quoted(const char *s, int i, char **out);
t_token	*append_token(t_token	*tail, t_token	*t);
void	free_tokens_list(t_token	*head);
int		push_op(t_token	**head, t_token	**tail, t_token_type type);
int		pipe_less_more_(char *str, int *i, t_token **head, t_token **tail);
int		extract_quoted_word(char *str, int *i, t_token **head, t_token **tail);
int		get_unquoted_word(char *str, int *i, t_token **head, t_token **tail);
int		ft_isspace_pp(char c, int *i);
void	init_lex(int *i, t_token **head, t_token **tail);

//helper functions 
int		redirect_choice(t_token **head, t_token **tail, char c);


//helper function for adding  cmd and its args (ls + -la); has issue does beyond what is asked
char **build_res_list(t_token *head);

//dispacher 
t_full_cmd	*dispatch_lexer_to_full_cmd(t_token *tokens);

//helper functions for dispatcher
void	add_expandable_var(t_ctx *ctx, t_token *head);


//misc
t_full_cmd	*initialize_cmd(void);
void	destroy(t_full_cmd **ptr_cmd);
int	run_line(t_ctx *ctx, char *line);
