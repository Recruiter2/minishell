/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 11:57:26 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/13 14:27:18 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

// walks throuh the buffer
// ret: 1 means found nl
static int	walk(t_buf *buf)
{
	while (*buf->pos != '\n' && buf->pos < buf->end)
	{
		buf->pos++;
	}
	if (buf->pos < buf->end)
	{
		buf->pos++;
		return (1);
	}
	else
		return (0);
}

static int	append(t_new_line *nl, const char *src, size_t n)
{
	char	*tmp;
	char	*itnew;
	char	*itold;

	tmp = malloc(sizeof(*tmp) * (nl->len + n + 1));
	if (!tmp)
		return (perror("malloc error"), 1);
	itnew = tmp;
	itold = nl->content;
	while (*itold)
	{
		*itnew = *itold;
		itnew++;
		itold++;
	}
	nl->len += n;
	while (n)
	{
		*itnew++ = *src++;
		n--;
	}
	*itnew = 0;
	free(nl->content);
	nl->content = tmp;
	return (0);
}

// ret 2 means, it reached end of file, -1 error while reading or malloc
static int	read_buf(int fd, t_buf *buf, t_new_line *nl)
{
	int			nb_read;
	const char	*begin;
	int			nl_found;

	if (buf->pos == buf->start)
	{
		nb_read = read(fd, buf->start, BUFFER_SIZE);
		if (nb_read == 0)
			return (2);
		else if (nb_read == -1)
			return (perror("read error"), -1);
		buf->end = buf->start + nb_read;
	}
	begin = buf->pos;
	nl_found = walk(buf);
	if (append(nl, begin, buf->pos - begin))
		return (-1);
	if (buf->pos == buf->end)
		buf->pos = buf->start;
	return (nl_found);
}

char	*get_next_line(int fd)
{
	static t_buf	buf[FOPEN_MAX];
	t_new_line		nl;
	int				done;

	if (!buf[fd].pos || !buf[fd].end)
	{
		buf[fd].pos = buf[fd].start;
		buf[fd].end = buf[fd].start;
	}
	nl.content = malloc(sizeof(*nl.content));
	if (!nl.content)
		return (perror("malloc error"), NULL);
	*nl.content = 0;
	nl.len = 0;
	done = 0;
	while (!done)
	{
		done = read_buf(fd, buf + fd, &nl);
		if (done == -1)
			return (free(nl.content), NULL);
	}
	if (done == 2 && *nl.content == 0)
		return (free(nl.content), NULL);
	return (nl.content);
}
