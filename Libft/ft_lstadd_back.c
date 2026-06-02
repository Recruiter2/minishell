/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 09:28:39 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/05/20 20:09:06 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new_)
{
	t_list	*nodelast;

	if (!lst && new_)
		return ;
	if (!*lst)
	{
		*lst = new_;
		return ;
	}
	nodelast = ft_lstlast(*lst);
	if (nodelast == NULL)
		*lst = new_;
	else if (nodelast)
		nodelast->next = new_;
}
