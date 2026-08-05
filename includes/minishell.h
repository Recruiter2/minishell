/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/04 15:26:52 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/06 01:02:57 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <ctype.h>
# include <stdlib.h>
# include <string.h>
# include "../Libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

//include executor
# include "get_next_line.h"
# include "executor.h"
# include "environment.h"
# include "prepare_execution.h"
# include "tokens.h"

// NULL-terminated: argv[0] is program, argv[1...] are args
// optional helper
typedef struct s_cmd
{
	char	**argv;
	int		argc;
}	t_cmd;

char		**ft_split(char const *s, char c);

//end of test from executor struct

//function for user input or parsing...
// this function check if readline is empty
int			is_blank(const char *s);
void		handle_input(void);

// history functions
void		add_shell_history(const char *line);
void		builtin_history(void);

// signaling
void		sigint_handler(int sig);

//lexer

t_token		*lexer(char *s);
void		free_tokens(t_token	*head);

t_token		*tok_new(t_token_type type, char *text, char quote);
int			consume_quoted(const char *s, int i, char **out);
t_token		*append_token(t_token	*tail, t_token	*t);
void		free_tokens_list(t_token	*head);
int			push_op(t_token	**head, t_token	**tail, t_token_type type);
int			pipe_less_more_(char *str, int *i, t_token **head, t_token **tail);
int			extract_quoted_word(char *str, int *i, \
t_token **head, t_token **tail);
int			get_unquoted_word(char *str, int *i, \
t_token **head, t_token **tail);
int			ft_isspace_pp(char c, int *i);
void		init_lex(int *i, t_token **head, t_token **tail);

//helper functions 
int			redirect_choice(t_token **head, t_token **tail, char c);

//helper function for adding  cmd and its args 
// (ls + -la); has issue does beyond what is asked
char		**build_res_list(t_token *head, t_ctx *ctx);

//dispacher 
void		dispatch_to_full_cmd(t_token *tokens, t_full_cmd *cmd, t_ctx *ctx);

//helper functions for dispatcher
void		add_expandable_var(t_ctx *ctx, t_token *head);
int			is_redir(t_token_type t);

//dispatcher_lib
void		add_segment(char **res, int *idx, char **seg);
void		consume_word(t_token **t, char **seg, t_ctx *ctx);
void		consume_redir(t_token **t);
//expansion functions
int			find_end(char *str);
size_t		extract_var_expan(char *str, t_ctx *ctx, char **seg);

//misc
t_full_cmd	*initialize_cmd(void);
void		destroy(t_full_cmd **ptr_cmd);
int			run_line(t_ctx *ctx, char *line);
//append word to the segment being built 
void		append_word(char **seg, char *word);
//supposed to detect the var to expand but actually does everything
//if var to expand no detected then adds up stuff
void		detect_start(char *str, t_ctx *ctx, char **seg);
//this function is used to know if we have a var
//  to expand thus to call ft detect_start
int			detect_var_expan(char *str);

#endif
