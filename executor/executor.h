/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:43:34 by marhuber          #+#    #+#             */
/*   Updated: 2026/06/28 20:39:01 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
* This represents an input file or a here document
* the name of the file or the delimiter character is a malloc'd string
* to destroy an element apply free() on the name
* @param name points at the beginning of the string 
* @param here_doc says if this is a here document
*/
typedef struct s_file_in
{
	char	*name;
	int		here_doc;
} 			t_file_in;

/**
* This is an element within a list of files in
* to destroy an element apply ad-hoc function
* @param content points at an instance of t_file_in
*/
typedef t_list t_list_file_in;

/**
* This represents an output file
* the name of the file is a malloc'd string
* the file can be opended in truncating or appending mode
* to destroy an element apply free() on the name
* @param name points at the beginning of a string containing a filename
* @param append says if content redictered at the output file is appended
*/
typedef struct s_file_out 
{
	char	*filename;
	int		append;
} 			t_file_out;

/**
* This is an element within a list of files out
* to destroy an element apply ad-hoc function
* @param content points at an instance of t_file_out
*/
typedef t_list t_list_file_out;

/**
* This represents a simple command with an exectuable and its arguments
* @param argv is defined as usual,  argv[0] is the executable, the args follow
* @param fdin stores the the fd for input
* @param fdout stores the the fd for output
* @param id stores the id of the subprocess in which argv is executed
*/
typedef struct s_simple_cmd
{
	int		fdin;
	int		fdout;
	pid_t	id;
	char	**argv;
} 			t_single_cmd;

/**
* This is an element within a list of simple commands
* @param content points at an instance of t_single_cmd
*/
typedef t_list t_list_single_cmd;

/**
* This contains all information on a full command
*/
typedef struct s_full_command
{
	t_list_file_in		*file_in;
	t_list_file_out		*file_out;
	t_list_single_cmd	*cmd;
}						t_full_cmd;



	

/*
< infile.txt grep "money" | cl -cw > outfile.txt 

*/




// internal types (used only within the executor)

typedef struct s_step_parameters
{
	int			fdin;
	int			fdout;
	pid_t		id;
}				t_step;


t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *newelem);
void	ft_lstclear(t_list **lst, void (*del)(void*));
