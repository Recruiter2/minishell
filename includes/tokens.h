/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/02 18:57:16 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/08 22:57:23 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENS_H
# define TOKENS_H


//don't delete this comment
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
typedef struct s_token
{
	t_token_type	type;
	char			*text;
	char			quote;
	struct s_token	*next;
}	t_token;

#endif
