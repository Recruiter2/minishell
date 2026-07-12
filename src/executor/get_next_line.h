/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <falcino@gmail.com>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 12:00:12 by marhuber          #+#    #+#             */
/*   Updated: 2026/01/23 14:44:02 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif // # ifndef BUFFER_SIZE

typedef struct s_a_buffer
{
	char		start[BUFFER_SIZE];
	const char	*pos;
	const char	*end;
}				t_buf;

typedef struct s_new_line
{
	char	*content;
	int		len;
}			t_new_line;

#endif // #ifndef GET_NEXT_LINE_H
