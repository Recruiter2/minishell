/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 21:01:10 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/20 21:01:14 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *str, char const *str0)
{
	size_t	lenstr;
	size_t	lenstr0;
	char	*res;

	if (!str && !str0)
		return (NULL);
	if (!str)
		return (ft_strdup(str0));
	if (!str0)
		return (ft_strdup(str));
	lenstr = ft_strlen(str);
	lenstr0 = ft_strlen(str0);
	res = malloc((lenstr + lenstr0 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	ft_strlcpy(res, (char *)str, lenstr + 1);
	ft_strlcat(res, (char *)str0, lenstr + lenstr0 + 1);
	return (res);
}
