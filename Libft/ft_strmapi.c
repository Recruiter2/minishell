/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 12:54:14 by tzinaliy          #+#    #+#             */
/*   Updated: 2025/10/25 12:54:16 by tzinaliy         ###   ###########       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const	*str, char (*f)(unsigned int, char))
{
	char			*res;
	unsigned int	lenstr;
	unsigned int	i;

	i = 0;
	if (!str || !f)
		return (NULL);
	lenstr = ft_strlen(str);
	res = malloc(lenstr + 1 * sizeof(char));
	if (!res)
		return (NULL);
	while (str[i])
	{
		res[i] = f(i, str[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}
