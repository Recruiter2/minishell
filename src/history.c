/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 14:55:56 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/04 13:16:16 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void add_shell_history(const char *line)
{
	if (!line || *line == '\0')
		return;
	add_history(line);

}

// Print history builtin: "history"
// start index at 1 to match bash
void builtin_history(void)
{
	int i;

	i = 0;
	HIST_ENTRY **hist_list = history_list();
	if (!hist_list) {
		return;
	}
	while ( hist_list[i] != NULL)
	{
		printf("%4d  %s\n", i + history_base, hist_list[i]->line);
		i++;
	}
}