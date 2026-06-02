/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 10:58:29 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/29 10:58:31 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*tmp;
	void	*transformed_content;

	tmp = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		transformed_content = f(lst->content);
		new_node = ft_lstnew(transformed_content);
		if (!new_node)
		{
			del(transformed_content);
			ft_lstclear(&tmp, del);
			return (NULL);
		}
		ft_lstadd_back(&tmp, new_node);
		lst = lst->next;
	}
	return (tmp);
}
