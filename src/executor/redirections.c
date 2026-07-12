/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 21:19:01 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/05 12:12:58 by marhuber         ###   ########.fr       */
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

static int	read_here_doc(char *delim, int *fd_pipe)
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
	*fd_pipe = pipedes[0];
	return (free(delim), 0);
}

int	prepare_redir(t_redir *redir, int *ptr_fd_in, int *ptr_fd_out)
{
	int	o_flag_out;

	if (redir->is_input)
	{
		if (redir->is_here_doc)
			read_here_doc(redir->name, ptr_fd_in);
		else
		{
			*ptr_fd_in = open(redir->name, O_RDONLY);
			if (*ptr_fd_in < 0)
				return (perror(redir->name), 1);
		}
	}
	else
	{
		if (redir->append_mode)
			o_flag_out = O_WRONLY | O_CREAT | O_APPEND;
		else
			o_flag_out = O_WRONLY | O_CREAT | O_TRUNC;
		*ptr_fd_out = open(redir->name, o_flag_out, 0664);
		if (*ptr_fd_out < 0)
			return (perror(redir->name), 1);
	}
	return (0);
}
