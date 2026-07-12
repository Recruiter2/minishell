/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:43:34 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/05 12:31:49 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H
# include <unistd.h>

/**
* this is an element of a linked list
* @param content points at the content, eg. a string or another construct
* @param next points at the next element in the list or is NULL, if none exists
* the variable and element pointed at exist outside of this element
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

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
* @param fdin stores the the fd for input
* @param fdout stores the the fd for output
* @param id stores the id of the subprocess in which argv is executed
*/
typedef struct s_simple_cmd
{
	char	**argv;
	int		fdin;
	int		fdout;
	pid_t	id;
}			t_single_cmd;

/**
* This is an element within a list of simple commands
* @param content points at an instance of t_single_cmd
*/
typedef t_list	t_list_single_cmd;

/**
* This contains all information on a full command
* @param redir points at the beginning of a list of redirections to be applied
* @param cmd points at the beginning of a list of comments to be executed
* @param
*/
typedef struct s_full_command
{
	t_list_redir		*redir;
	t_list_single_cmd	*cmd;
	int					fdin;
	int					fdout;
}						t_full_cmd;

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *newelem);
void	ft_lstclear(t_list **lst, void (*del)(void*));

#endif