/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 21:19:01 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/11 10:27:15 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include "../../includes/executor.h"

char	*str_piece_dup(char *start, char *end);
char	*evar_expansion(t_ctx *ctx, char *name);
int		ft_isalpha(char c);
int		ft_isalnum(char c);
char	*join_str_c_str(char const *s1, char c, char const *s2);
int		put_str_fd(const char *s, int fd);
char	*get_next_line(int fd);
int		ft_strcmp(const char *s1, const char *s2);

int	feed_expansion(t_ctx *ctx, char *name_start, char *name_end, int fd)
{
	char	*name;
	char	*value;

	name = str_piece_dup(name_start, name_end);
	if (!name)
		return (1);
	value = evar_expansion(ctx, name);
	free(name);
	if (!value)
		return (0);
	else
	{
		while (*value)
		{
			if (write(fd, value++, 1) < 0)
				return (perror("feeding heredoc pipe"), 1);
		}
	}
	return (0);
}

int	feed_line(t_ctx *ctx, char *line, int fd)
{
	char	*name;

	while (*line)
	{
		if (*line != '$')
		{
			if (write(fd, line++, 1) < 0)
				return (perror("feeding heredoc pipe"), 1);
		}
		else
		{
			name = ++line;
			if (*line == '?')
				feed_expansion(ctx, name, ++line, fd);
			else if (*line == '_' || ft_isalpha(*line))
			{
				line++;
				while (*line == '_' || ft_isalnum(*line))
					line++;
				feed_expansion(ctx, name, line, fd);
			}
		}
	}
	return (0);
}

static int	read_here_doc(t_ctx *ctx, char *delim, int *fd_pipe)
{
	char	*line;
	int		pipedes[2];

	if (pipe(pipedes))
		return (perror("error pipe"), 1);
	delim = join_str_c_str(delim, '\n', "");
	if (!delim)
		return (perror("malloc error"), 1);
	put_str_fd("> ", ctx->fd_stdout);
	line = get_next_line(ctx->fd_stdin);
	if (!line)
		return (put_str_fd("minishell: get_next_line", 2), 1);
	while (ft_strcmp(line, delim))
	{
		feed_line(ctx, line, pipedes[1]);
		put_str_fd("> ", ctx->fd_stdout);
		free(line);
		line = get_next_line(ctx->fd_stdin);
	}
	free(line);
	if (close(pipedes[1]))
		return (perror("close pipe end in read_here_doc"), 1);
	*fd_pipe = pipedes[0];
	return (free(delim), 0);
}

static int	apply_redir(t_ctx *ctx, t_redir *redir, int *ptr_fd)
{
	int	o_flag_out;

	if (redir->is_output)
	{
		if (redir->append_mode)
			o_flag_out = O_WRONLY | O_CREAT | O_APPEND;
		else
			o_flag_out = O_WRONLY | O_CREAT | O_TRUNC;
		*ptr_fd = open(redir->name, o_flag_out, 0664);
		if (*ptr_fd < 0)
			return (perror(redir->name), 1);
		return (0);
	}
	if (redir->is_here_doc)
	{
		if (read_here_doc(ctx, redir->name, ptr_fd))
			return (1);
	}
	else
	{
		*ptr_fd = open(redir->name, O_RDONLY);
		if (*ptr_fd < 0)
			return (perror(redir->name), 1);
	}
	return (0);
}

int	apply_all_redir(t_ctx *ctx, t_list_redir *it_redir)
{
	t_redir	*redir;
	int		fd;

	while (it_redir)
	{
		redir = it_redir->content;
		if (apply_redir(ctx, redir, &fd))
			return (1);
		if (dup2(fd, redir->is_output) < 0)
			return (perror("dup2 in apply_all_redir"), 1);
		if (close(fd))
			return (perror("close fd in apply_all_redir"), 1);
		it_redir = it_redir->next;
	}
	return (0);
}
