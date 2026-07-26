/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:07:20 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/26 22:25:01 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options
*/
#include "../../includes/environment.h"
#include "../../includes/executor.h"
#include "../../includes/lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int			ft_strcmp(const char *s1, const char *s2);
const char	*ft_strchr(const char *str, char c);
void		end(t_ctx *ctx, t_full_cmd *cmd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *newelem);
int			bi_export(char **argv, t_ctx *ctx);
int			bi_unset(char **argv, t_ctx *ctx);

int	bi_echo(char **argv, t_ctx *ctx)
{
	char	**start;
	char	**it;
	char	*trailing;

	(void)ctx;
	trailing = "\n";
	start = argv + 1;
	if (*start)
	{
		if (ft_strcmp(*start, "-n") == 0)
		{
			trailing = "";
			start++;
		}
		it = start;
		while (*it)
		{
			if (it != start)
				printf(" ");
			printf("%s", *it++);
		}
	}
	printf ("%s", trailing);
	return (0);
}

int	bi_exit(char **argv, t_ctx *ctx)
{
	(void)argv;
	(void)ctx;
	return (0);
}

int	add_one_bi(char *name, int (*ft)(char **, t_ctx *), t_list_bi **list)
{
	t_builtin	*content;
	t_list_bi	*tmp;

	content = malloc (sizeof(*content));
	if (!content)
		return (perror("malloc error"), 1);
	content->name = name;
	content->ft = ft;
	tmp = ft_lstnew(content);
	if (!tmp)
		return (1);
	ft_lstadd_back(list, tmp);
	return (0);
}

int	add_all_bi(t_list_bi **builtins)
{
	int	err;

	*builtins = NULL;
	err = 0;
	err += add_one_bi("echo", &bi_echo, builtins);
	err += add_one_bi("export", &bi_export, builtins);
	err += add_one_bi("unset", &bi_unset, builtins);
	err += add_one_bi("exit", &bi_exit, builtins);
	if (err)
		return (1);
	else
		return (0);
}

t_builtin	*is_builtin(char *name, t_list_bi *builtins)
{
	t_list_bi	*it_bi;
	t_builtin	*builtin_cmd;

	if (ft_strchr(name, '/'))
		return (NULL);
	it_bi = builtins;
	while (it_bi)
	{
		builtin_cmd = it_bi->content;
		if (ft_strcmp(name, builtin_cmd->name))
			it_bi = it_bi->next;
		else
			return (builtin_cmd);
	}
	return (NULL);
}

int	exec_builtin(t_single_cmd *single_cmd, t_ctx *ctx, t_full_cmd *full_cmd)
{
	int	ret;

	ret = (*single_cmd->builtin->ft)(single_cmd->argv, ctx);
	if (ft_strcmp(single_cmd->builtin->name, "exit") == 0)
	{
		end(ctx, full_cmd);
		exit (0);
	}
	return (ret);
}
