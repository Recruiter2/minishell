/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 18:30:08 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/05/27 18:53:44 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_grid(void **grid)
{
	void	**p;

	if (!grid)
		return ;
	p = grid;
	while (*p)
	{
		free(*p);
		p++;
	}
	if (grid)
		free(grid);
	grid = NULL;
}
