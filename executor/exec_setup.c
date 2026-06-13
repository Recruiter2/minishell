/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:52:41 by marhuber          #+#    #+#             */
/*   Updated: 2026/06/13 15:18:48 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include "executor.h"

char	*ft_strjoin(char const *s1, char const *s2);
char	*get_next_line(int fd);
int		ft_strcmp(const char *s1, const char *s2);
void	putstrfd(const char *s, int fd);

/**
* tries to find the executable in the current working directory [...]
* if not found tries to find it in PATH
* if found in PATH, the executable is given an absolute PATH 
* if not found in PATH does not do anything
*/
int	find_cmd(char **path, t_singlecmd argv)
{
	char	*tmp;

	if (access(*argv, F_OK))
	{
		while (*path)
		{
			tmp = ft_strjoin(*path, *argv);
			if (!tmp)
				return (1);
			if (access(tmp, F_OK))
			{
				free(tmp);
				path++;
			}
			else
			{
				free(*argv);
				*argv = tmp;
				return (0);
			}
		}
	}
	return (0);
}

static int	read_here_doc(char *delim, int *fd_to_file)
{
	char	*line;
	int		pipedes[2];

	if (pipe(pipedes))
		return (perror("error pipe"), 1);
	delim = ft_strjoin(delim, "\n");
	putstrfd("pipe heredoc> ", 1);
	line = get_next_line(0);
	while (ft_strcmp(line, delim))
	{
		putstrfd(line, pipedes[1]);
		putstrfd("pipe heredoc> ", 1);
		free(line);
		line = get_next_line(0);
	}
	free(line);
	close(pipedes[1]);
	*fd_to_file = pipedes[0];
	return (free(delim), 0);
}

static int	openoutfile(t_fullcmd *fullcmd, t_step *stepcol, int n)
{
	int	o_flag_out;

	if (fullcmd->namefileout)
	{
		if (fullcmd->fileout_append)
			o_flag_out = O_WRONLY | O_CREAT | O_APPEND;
		else
			o_flag_out = O_WRONLY | O_CREAT | O_TRUNC;
		stepcol[n - 1].fdout = open(fullcmd->namefileout, o_flag_out, 0664);
		if (stepcol[n - 1].fdout < 0)
			return (perror(fullcmd->namefileout), 1);
	}
	else
		stepcol[n - 1].fdout = 1;
	return (0);
}

int	openfiles(t_fullcmd *fullcmd, t_step *stepcol, int n)
{
	if (fullcmd->namefilein)
	{
		stepcol[0].fdin = open(fullcmd->namefilein, O_RDONLY);
		if (stepcol[0].fdin < 0)
			return (perror(fullcmd->namefilein), 1);
	}
	else if (fullcmd->heredocdelim)
	{
		if (read_here_doc(fullcmd->heredocdelim, &stepcol[0].fdin))
			return (1);
	}
	else
		stepcol[0].fdin = 0;
	return (openoutfile(fullcmd, stepcol, n));
}
