/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/11 10:21:03 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/11 10:26:33 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	put_str_fd(const char *s, int fd)
{
	while (*s)
	{
		if (write(fd, s, 1) < 0)
			return (perror("put_str_fd"), 1);
		s++;
	}
	return (0);
}

char	*str_piece_dup(char *start, char *end)
{
	char	*ret;
	char	*it;

	ret = malloc (sizeof(*ret) * (end - start + 1));
	if (!ret)
		return (perror("malloc error"), NULL);
	it = ret;
	while (start < end)
	{
		*it = *start;
		it++;
		start++;
	}
	*it = 0;
	return (ret);
}
