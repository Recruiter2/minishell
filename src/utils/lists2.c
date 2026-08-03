/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/17 21:44:32 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/02 16:44:26 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../../includes/lists.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	(*del)(lst->content);
	free(lst);
}

void	ft_lstclear(t_list **ptlst, void (*del)(void*))
{
	if (!*ptlst)
		return ;
	(*del)((*ptlst)->content);
	if ((*ptlst)->next)
		ft_lstclear(&((*ptlst)->next), del);
	free(*ptlst);
	*ptlst = NULL;
	return ;
}
