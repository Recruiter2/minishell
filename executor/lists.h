/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/11 11:47:38 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/14 01:30:50 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LISTS_H
# define LISTS_H
# include <unistd.h>

/**
* this is an element of a linked list
* @param content points at the content, eg. a string or another construct
* @param next points at the next element in the list or is NULL, if none exists
* the variable or element pointed at exist outside of this element
*/
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

#endif