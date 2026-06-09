/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:29:04 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/09 22:32:10 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "../Libft/libft.h"
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

typedef	enum
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_REDIR_APPEND,
	T_HEREDOC
} token_type;
// <
// >
// >>
// <<

// raw text (without surrounding quotes)
// 0 = none, '\'' or '"' if entire token was quoted
typedef struct	token
{
	token_type	type;
	char	*text;
	char	quote;
	struct token	*next;
} token_t;


//function for user input or parsing...
// this function check if readline is empty
int is_blank(const char *s);
void	handle_input(void);

// history functions
void add_shell_history(const char *line);
void builtin_history(void);

// signaling
void sigint_handler(int sig);

//lexer

token_t *lexer(const char *s);

