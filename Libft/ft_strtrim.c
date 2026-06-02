/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 12:50:54 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/21 12:52:01 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *str, char const *set)
{
	char	*res;
	size_t	lenstr;
	size_t	i;

	i = 0;
	if (!str)
		return (NULL);
	if (!set)
		return (ft_strdup(str));
	lenstr = ft_strlen(str);
	while (i < lenstr && ft_strrchr(set, str[i]))
	{
		i++;
	}
	while (str[lenstr - 1] && ft_strrchr(set, str[lenstr - 1]))
	{
		lenstr--;
	}
	res = ft_substr(str, i, lenstr - i);
	return (res);
}
