/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:44:32 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/13 23:39:03 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "lists.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*ret;

	ret = malloc(sizeof(t_list));
	if (!ret)
		return (NULL);
	ret->content = content;
	ret->next = 0;
	return (ret);
}

int	ft_lstsize(t_list *lst)
{
	int	re;

	re = 0;
	while (lst)
	{
		lst = lst->next;
		re++;
	}
	return (re);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst)
	{
		if (lst->next)
			lst = lst->next;
		else
			break ;
	}
	return (lst);
}

void	ft_lstadd_back(t_list **ptlst, t_list *new)
{
	t_list	*last;

	if (*ptlst)
	{
		last = ft_lstlast(*ptlst);
		last->next = new;
	}
	else
		*ptlst = new;
}

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	(*del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	(*del)((*lst)->content);
	if ((*lst)->next)
		ft_lstclear(&((*lst)->next), del);
	free(*lst);
	*lst = 0;
}
