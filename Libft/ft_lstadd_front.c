/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 21:15:55 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/05/20 20:10:03 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new_)
{
	if (!new_ && !lst)
		return ;
	if (!lst)
	{
		*lst = new_;
		return ;
	}
	new_->next = *lst;
	*lst = new_;
}
