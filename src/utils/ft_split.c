/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/26 21:34:21 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/17 16:25:59 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static size_t	count_entries(char const *s, char c)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!in_word)
			{
				count++;
				in_word = 1;
			}
		}
		else
			in_word = 0;
		s++;
	}
	return (count);
}

static int	malloc4subs(char **subs, int amount_subs, const char *str, char c)
{
	size_t	count;

	while (amount_subs)
	{
		while (*str == c)
			str++;
		count = 0;
		while (*str != c && *str != 0)
		{
			str++;
			count++;
		}
		*subs = malloc(sizeof(**subs) * (count + 1));
		if (!*subs)
			return (perror("Malloc error"), 1);
		subs++;
		amount_subs--;
	}
	*subs = 0;
	return (0);
}

static void	fill_substrings(char **subs, const char *str, char c)
{
	char	*p;

	while (*subs)
	{
		while (*str == c)
			str++;
		p = *subs;
		while (*str != c && *str != 0)
		{
			*p = *str;
			p++;
			str++;
		}
		*p = 0;
		subs++;
	}
}

void	free_all(char ***strs)
{
	char	**it;

	it = *strs;
	while (*it)
	{
		free(*it);
		*it = 0;
		it++;
	}
	free(*strs);
	*strs = 0;
}

/**
* Reads a string composed by words separated by a given character
* Returns a collection of substrings, each containing a word
* Orders substrings as they appear in the input string
* Repeats words if they appear multiple times in the input string
* Does not create empty strings
* Malloc's each string in the collection separatedly
*
* @param s points to the beginning of a 0-terminated string
* @param c is a character that might be contained in s
* @return a NULL-terminated array of pointers to the substrings
*/
char	**ft_split(char const *s, char c)
{
	char	**ret;
	size_t	len_ret;

	len_ret = count_entries(s, c);
	if (!len_ret)
		len_ret++;
	ret = malloc(sizeof(*ret) * (len_ret + 1));
	if (!ret)
		return (perror("Malloc error"), NULL);
	if (malloc4subs(ret, len_ret, s, c))
		return (free_all(&ret), NULL);
	fill_substrings(ret, s, c);
	return (ret);
}
