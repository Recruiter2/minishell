/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:07:20 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/16 19:53:50 by marhuber         ###   ########.fr       */
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
#include "environment.h"
#include "executor.h"
#include "lists.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_strcmp(const char *s1, const char *s2);
const char	*ft_strchr(const char *str, char c);

t_list	*ft_lstnew(void *content);
void	ft_lstadd_back(t_list **lst, t_list *newelem);

int	bi_echo(char **argv, t_list_ev *env_lst)
{
	char	*trailing;

	(void)env_lst;
	trailing = "\n";
	argv++;
	if (*argv)
	{
		if (ft_strcmp(*argv, "-n") == 0)
		{
			trailing = "";
			argv++;
		}
		while (*argv)
			printf("%s", *argv++);
	}
	printf ("%s", trailing);
	return (0);
}

int	add_one_bi(char *name, int (*ft)(char **, t_list_ev *), t_list_bi **builtins)
{
	t_builtin	*content;
	t_list_bi	*tmp;

	content = malloc (sizeof(*content));
	if (!content)
		return (1); // perror?
	content->name = name;
	content->ft = ft;
	tmp = ft_lstnew(content);
	if (!tmp)
		return (1);
	ft_lstadd_back(builtins, tmp);
	return (0);	
}

int	add_all_bi(t_list_bi **builtins)
{
	int	err;

	*builtins = NULL;
	err = 0;
	err += add_one_bi("echo", &bi_echo, builtins);
	
	if(err)
		return(1);
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

int	exec_builtin(t_single_cmd *single_cmd, t_ctx *ctx)
{
	return((*single_cmd->builtin->ft)(single_cmd->argv, ctx->env_lst));
}