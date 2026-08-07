/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher_helper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/05 22:20:16 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/08/07 21:45:30 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdio.h>

int	is_redir(t_token_type t)
{
	return (t == T_REDIR_IN || t == T_REDIR_OUT \
|| t == T_REDIR_APPEND || t == T_HEREDOC);
}

//this function appends word to the segment that will be used obviously
// no need to grow: existing + (space if needed) + word + '\0'
//strlcpy copy old content obviously
// whatever is using append_word segments if token we need to add space
void	append_word(char **seg, char *word)
{
	char	*temp;
	size_t	seglen;
	size_t	wlen;

	if (!word)
		return ;
	wlen = ft_strlen(word);
	if (*seg == NULL)
	{
		*seg = ft_strdup(word);
		return ;
	}
	seglen = ft_strlen(*seg);
	temp = ft_calloc(seglen + wlen + 1, sizeof(char));
	if (!temp)
		exit(1);
	ft_strlcpy(temp, *seg, seglen + 1);
	ft_strcat(temp, word);
	free(*seg);
	*seg = temp;
}


