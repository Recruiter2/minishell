/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:43:34 by marhuber          #+#    #+#             */
/*   Updated: 2026/06/06 17:25:51 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <unistd.h>


// External types (used to communicate to the executor)

typedef struct s_contextual_information
{
	char	**path;			// array of strings containing directories in PATH
	char	**envp;
}			t_ctx;

/*
an element of type t_singlecmd points at a NULL-terminated array of strings
to be used when the first string represents a command and the following strings
	represent the parameters of such command
(ex. "char **argv" is equivalent to "t_singlecmd argv")
*/
typedef char	**t_singlecmd;

/*
< infile.txt grep "money" | cl -cw > outfile.txt 

cmds -> cmds[0] -> cmds[0][0] -> "grep" -> 'g'
				   cmds[0][1] -> "money"
				   cmds[0][2] == NULL
	 -> cmds[1]	-> cmds[1][0] -> "cl"
	 			-> cmds[1][1] -> "-cw"
				   cmds[1][2] == NULL
	-> cmds[2] == NULL
*/

/*
This struct contains all the information needed to execute a full command
A full command can contain pipes and simple redirections (|, <, >)
namefilein is NULL if there is no infile (<)
namefileout is NULL if the is no outfile (>)
cmpds points at the beginning of a NULL-terminated array of pointers
*/
typedef struct s_full_command
{
	// int		here_doc;		// here_doc instead of file1
	char		*namefilein;
	char		*namefileout;
	t_singlecmd	*cmds;
}				t_fullcmd;


// internal types (used only within the executor)

typedef struct s_step_parameters
{
	int			fdin;
	int			fdout;
	pid_t		id;
	// t_singlecmd argv;
}				t_step;

// typedef struct s_composite_command
// {
// 	// int		n;				// amount of shell commands in the sequence
// 	// int		here_doc;		// here_doc instead of file1
// 	// int		fdheredocpipe;
// 	char	*namefilein;
// 	char	*namefileout;
// 	t_step	*stepcol;		// points to the array of steps parameters
// }			t_compcom;