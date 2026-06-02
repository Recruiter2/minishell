/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 18:52:20 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/26 18:52:22 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*my_list;

	my_list = malloc(16);
	if (!my_list)
	{
		return (NULL);
	}
	my_list->content = content;
	my_list->next = NULL;
	return (my_list);
}
