/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 14:57:46 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/20 14:57:49 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *str, unsigned int start, size_t len)
{
	size_t	lenstr;
	size_t	i;
	char	*res;

	if (!str)
		return (NULL);
	lenstr = ft_strlen(str);
	i = 0;
	if (start >= lenstr)
		return (ft_strdup(""));
	if (len > lenstr - start)
		len = lenstr - start;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len)
	{
		res[i] = str[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}
