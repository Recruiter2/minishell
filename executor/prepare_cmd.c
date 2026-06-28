/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:11:07 by marhuber          #+#    #+#             */
/*   Updated: 2026/06/28 20:41:51 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "executor.h"

// char	*ft_strdup(const char *src);

t_full_cmd	*initialize_cmd(void)
{
	t_full_cmd	*ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (NULL); // perror?
	ret->file_in = NULL;
	ret->file_out = NULL;
	ret->cmd = NULL;
	return (ret);
}

int	add_file_in(t_full_cmd *cmd, char* filename)
{
	t_file_in		*content;
	t_list_file_in	*tmp;

	content = malloc (sizeof(*content));
	if (!content)
		return (1); // perror?
	content->name = filename;
	content->here_doc = 0;
	tmp = ft_lstnew(content);
	if (!(tmp))
		return (1); 
	ft_lstadd_back(&cmd->file_in, tmp);
	return (0);
}

int	add_here_doc(t_full_cmd *cmd, char* delimiter)
{
	t_file_in		*content;
	t_list_file_in	*tmp;

	content = malloc (sizeof(*content));
	if (!content)
		return (1); // perror?
	content->name = delimiter;
	content->here_doc = 1;
	tmp = ft_lstnew(content);
	if (!(tmp))
		return (1); 
	ft_lstadd_back(&cmd->file_in, tmp);
	return (0);
}

int	add_file_out(t_full_cmd *cmd, char* filename, int append)
{
	t_file_out		*content;
	t_list_file_out	*tmp;

	content = malloc (sizeof(*content));
	if (!content)
		return (1); // perror?
	content->filename = filename;
	content->append = append;
	tmp = ft_lstnew(content);
	if (!(tmp))
		return (1); 
	ft_lstadd_back(&cmd->file_out, tmp);
	return (0);
}

int	add_single_cmd(t_full_cmd *cmd, char **argv)
{
	t_single_cmd		*content;
	t_list_single_cmd	*tmp;

	content = malloc (sizeof(*content));
	if (!content)
		return (1); // perror?
	content->argv = argv;
	tmp = ft_lstnew(content);
	if (!(tmp))
		return (1); 
	ft_lstadd_back(&cmd->cmd, tmp);
	return (0);
}
