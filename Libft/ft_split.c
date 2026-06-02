/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 13:31:28 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/04/27 15:00:46 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

size_t	size_word(char const *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] && (str[i] != (unsigned char)c))
	{
		i++;
	}
	return (i);
}

size_t	count_words(const char *str, char c)
{
	size_t	i;
	size_t	nb_words;

	i = 0;
	nb_words = 0;
	while (str[i])
	{
		if (str[i] != (unsigned char)c)
		{
			nb_words++;
			i += size_word(&str[i], c);
		}
		else
			i++;
	}
	return (nb_words);
}

static	void	*free_array(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	size_t	arraybig;
	size_t	j;

	j = 0;
	if (!str)
		return (NULL);
	arraybig = count_words(str, c);
	res = ft_calloc((arraybig + 1), sizeof(char *));
	if (!res)
		return (NULL);
	while (*str)
	{
		if (*str != c)
		{
			res[j] = ft_substr(str, 0, size_word(str, c));
			if (!res[j++])
				return (free_array(res));
			str += size_word(str, c);
		}
		else
			str++;
	}
	return (res);
}
