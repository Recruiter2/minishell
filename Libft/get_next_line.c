/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/06 18:52:02 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/05/12 13:50:27 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
	*/
/*
void	*ft_calloc(size_t n, size_t size)
{
	size_t	i;
	char	*tmp;
	size_t	bytes;

	i = 0;
	if (n == 0 || size == 0)
		return (NULL);
	bytes = size * n;
	tmp = malloc(bytes * sizeof(char));
	if (!tmp)
		return (free(tmp), NULL);
	while (i < bytes)
	{
		tmp[i] = '\0';
		i++;
	}
	return (tmp);
}
*/
char	*read_from_file(char *res_buffer, int fd)
{
	int			bytes_read;
	char		*buffer;
	char		*temp;

	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free(buffer), NULL);
	while (bytes_read > 0)
	{
		if (bytes_read <= 0)
			break ;
		buffer[bytes_read] = '\0';
		temp = ft_strjoin(res_buffer, buffer);
		free(res_buffer);
		res_buffer = temp;
		if (ft_strchr(res_buffer, '\n'))
			break ;
		bytes_read = read(fd, buffer, BUFFER_SIZE);
	}
	return (free(buffer), res_buffer);
}

void	free_buffer(char **res_buffer)
{
	free(*res_buffer);
	*res_buffer = NULL;
}

char	*get_next_line(int fd)
{
	static char	*res_buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!res_buffer)
		res_buffer = ft_calloc(1, sizeof(char));
	temp = read_from_file(res_buffer, fd);
	if (!temp)
		return (free_buffer(&res_buffer), NULL);
	res_buffer = temp;
	if (!res_buffer || res_buffer[0] == '\0')
		return (free_buffer(&res_buffer), NULL);
	line = extract_line(res_buffer);
	temp = trim_buffer(res_buffer);
	free(res_buffer);
	res_buffer = temp;
	return (line);
}
/*
int	main(void)
{
	int		fd;
	char	*line;
	int		count;

	count = 0;
	fd = open("read_error.txt", O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file");
		return (1);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		count++;
		printf("%s", line); //count is to show the line numbers
		//	printf("memory allocated\n");
		free(line);
		line = NULL;
	}
	close(fd);
	return (0);
}
*/
