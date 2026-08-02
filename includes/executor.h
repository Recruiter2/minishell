/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:43:34 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/02 11:52:55 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

# include "environment.h"

/**
* This represents a redirection: an input file, a here document or an output file
* the name of the file or the delimiter is a string
* @param is_input says if the redirection is an input (< or <<)
* @param is_here_doc says if this is a here document (<<)
* @param append_mode says if the output file is to open in append mode (>>)
* @param name points at the beginning of the string
*/
typedef struct s_redirection
{
	int		is_input;
	int		is_here_doc;
	int		append_mode;
	char	*name;
}			t_redir;

/**
* This is an element within a list of redirections
* @param content points at an instance of t_redir
*/
typedef t_list	t_list_redir;

/**
* This represents a simple command with an exectuable and its arguments
* @param argv is defined as usual, argv[0] is the executable, the args follow
* @param redir points at the beginning of a list of redirections to be applied
* @param builtin says if the command is a builtin and points to it
* @param fdin stores the the fd for input
* @param fdout stores the the fd for output
* @param id stores the id of the subprocess in which argv is executed
*/
typedef struct s_simple_cmd
{
	t_list_redir	*redir;
	char			**argv;
	t_builtin		*builtin;
	int				fdin;
	int				fdout;
	pid_t			id;
}					t_single_cmd;

/**
* This is an element within a list of simple commands
* @param content points at an instance of t_single_cmd
*/
typedef t_list	t_list_single_cmd;

/**
* This contains all information on a full command
* @param cmd points at the beginning of a list of commands to be executed
*/
typedef struct s_full_command
{
	t_list_single_cmd	*cmd;
}						t_full_cmd;

#endif
