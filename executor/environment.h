/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 11:47:38 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/14 14:40:59 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENVIRONMENT_H
# define ENVIRONMENT_H
# include <unistd.h>
# include "lists.h"

/**
* This represents an environment variable
* @param name is the name of the variable (e.g. "PWD")
* @param value is the value of the variable (e.g. "/home/marhuber")
*/
typedef struct s_environment_variable
{
	char	*name;
	char	*value;
}			t_evar;

/**
* This is an element within a list of environt variables
* @param content points at an instance of t_evar
*/
typedef t_list	t_list_ev;

/**
* This represents a builtin command
* @param name is the name of the builtin (e.g. "echo")
* @param ft points at the function that executes the builtin
*/
typedef struct s_builtin_command
{
	char	*name;
	int		(*ft)(char **, t_list_ev *);
}			t_builtin;

/**
* This is an element within a list of environt variables
* @param content points at an instance of t_builtin
*/
typedef t_list	t_list_bi;

/**
* This structure contains the information necessary across the entire program
* The programm initializes one instance at the start
* @param env_strs saves the environment variables as an array of strings
* @param env_lst saves the environment variables as a linked list	
* @param path_strs saves the directories in PATH as an array of strings
* @param exit_status saves the exit status of the most recent full command
*/
typedef struct s_contextual_information
{
	t_list_ev	*env_lst;
	char		**env_strs;
	char		**path;
	t_list_bi	*builtins;
	int				exit_status;
}			t_ctx;
#endif