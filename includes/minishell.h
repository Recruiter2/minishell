/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:29:04 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/07/08 00:01:06 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

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


//helper functions for concatenating cmd and args 
char **build_res_list(t_token *head);
int is_redir(t_token_type t);
void append_word(char **seg, const char *w);



//helper functions for test of cmd and args concatenation
void	print_res(char **res);
void	free_res(char **res);
int	str_arr_eq(char **a, char **b);
