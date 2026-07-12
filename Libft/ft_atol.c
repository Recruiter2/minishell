/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/27 13:36:26 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/05/27 19:01:32 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* helpers - put these in a .c (or .h) alongside your libft functions */
#include <errno.h>
#include <limits.h>
#include <stdio.h>

static char	skip_spaces(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && (s[i] == ' ' || (s[i] >= '\t' && s[i] <= '\r')))
		i++;
	return (*(s + i));
}

static int	get_sign(const char **s)
{
	int	sign;

	sign = 1;
	if (**s == '+' || **s == '-')
	{
		if (**s == '-')
			sign = -1;
		(*s)++;
	}
	return (sign);
}

static unsigned long	accumulate(const char **s)
{
	unsigned long	acc;

	acc = 0;
	while (**s && (**s >= '0' && **s <= '9'))
	{
		acc = acc * 10 + (unsigned long)(**s - '0');
		(*s)++;
	}
	return (acc);
}

/* final function */

long	ft_atol(const char *str)
{
	int				sign;
	unsigned long	acc;

	if (!str)
		return (0);
	skip_spaces(str);
	sign = get_sign(&str);
	if (!(*str >= '0' && *str <= '9'))
		return (0);
	acc = accumulate(&str);
	if (sign == 1 && acc > (unsigned long)LONG_MAX)
	{
		errno = ERANGE;
		return (LONG_MAX);
	}
	if (sign == -1 && acc > (unsigned long)LONG_MAX + 1UL)
	{
		errno = ERANGE;
		return (LONG_MIN);
	}
	return ((long)acc * sign);
}
