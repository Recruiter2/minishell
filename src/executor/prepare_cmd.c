/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:11:07 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/17 18:34:03 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../../includes/executor.h"

t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *newelem);

t_full_cmd	*initialize_cmd(void)
{
	t_full_cmd	*ret;

	ret = malloc(sizeof(*ret));
	if (!ret)
		return (perror("malloc error"), NULL);
	ret->redir = NULL;
	ret->cmd = NULL;
	ret->fdin = 0;
	ret->fdout = 1;
	return (ret);
}

int	add_file_in(t_full_cmd *cmd, char *filename)
{
	t_redir			*content;
	t_list_redir	*tmp;

	content = malloc (sizeof(*content));
	if (!content)
		return (perror("malloc error"), 1);
	content->is_input = 1;
	content->is_here_doc = 0;
	content->name = filename;
	tmp = ft_lstnew(content);
	if (!tmp)
		return (1);
	ft_lstadd_back(&cmd->redir, tmp);
	return (0);
}

int	add_here_doc(t_full_cmd *cmd, char *delimiter)
{
	t_redir			*content;
	t_list_redir	*tmp;

	content = malloc (sizeof(*content));
	if (!content)
		return (perror("malloc error"), 1);
	content->is_input = 1;
	content->is_here_doc = 1;
	content->name = delimiter;
	tmp = ft_lstnew(content);
	if (!tmp)
		return (1);
	ft_lstadd_back(&cmd->redir, tmp);
	return (0);
}

int	add_file_out(t_full_cmd *cmd, char *filename, int append)
{
	t_redir			*content;
	t_list_redir	*tmp;

	content = malloc (sizeof(*content));
	if (!content)
		return (perror("malloc error"), 1);
	content->is_input = 0;
	content->append_mode = append;
	content->name = filename;
	tmp = ft_lstnew(content);
	if (!tmp)
		return (1);
	ft_lstadd_back(&cmd->redir, tmp);
	return (0);
}

int	add_single_cmd(t_full_cmd *cmd, char **argv)
{
	t_single_cmd		*content;
	t_list_single_cmd	*tmp;

	content = malloc (sizeof(*content));
	if (!content)
		return (perror("malloc error"), 1);
	content->argv = argv;
	tmp = ft_lstnew(content);
	if (!tmp)
		return (1);
	ft_lstadd_back(&cmd->cmd, tmp);
	return (0);
}
