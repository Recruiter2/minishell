/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/28 19:11:07 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/02 16:33:15 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../../includes/executor.h"

t_list	*ft_lstnew(void *content);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *newelem);

int	add_file_in(t_full_cmd *cmd, char *filename)
{
	t_redir			*content;
	t_list_redir	*tmp;
	t_single_cmd	*last_single_cmd;

	content = malloc (sizeof(*content));
	if (!content)
		return (perror("malloc error"), 1);
	content->is_output = 0;
	content->is_here_doc = 0;
	content->name = filename;
	tmp = ft_lstnew(content);
	if (!tmp)
		return (1);
	last_single_cmd = ft_lstlast(cmd->cmd)->content;
	ft_lstadd_back(&last_single_cmd->redir, tmp);
	return (0);
}

int	add_here_doc(t_full_cmd *cmd, char *delimiter)
{
	t_redir			*content;
	t_list_redir	*tmp;
	t_single_cmd	*last_single_cmd;

	content = malloc (sizeof(*content));
	if (!content)
		return (perror("malloc error"), 1);
	content->is_output = 0;
	content->is_here_doc = 1;
	content->name = delimiter;
	tmp = ft_lstnew(content);
	if (!tmp)
		return (1);
	last_single_cmd = ft_lstlast(cmd->cmd)->content;
	ft_lstadd_back(&last_single_cmd->redir, tmp);
	return (0);
}

int	add_file_out(t_full_cmd *cmd, char *filename, int append)
{
	t_redir			*content;
	t_list_redir	*tmp;
	t_single_cmd	*last_single_cmd;

	content = malloc (sizeof(*content));
	if (!content)
		return (perror("malloc error"), 1);
	content->is_output = 1;
	content->append_mode = append;
	content->name = filename;
	tmp = ft_lstnew(content);
	if (!tmp)
		return (1);
	last_single_cmd = ft_lstlast(cmd->cmd)->content;
	ft_lstadd_back(&last_single_cmd->redir, tmp);
	return (0);
}
