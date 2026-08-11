/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_ctx_exit.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/08 16:07:20 by marhuber          #+#    #+#             */
/*   Updated: 2026/08/11 10:31:40 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include "../../includes/executor.h"

t_list		*ft_lstnew(void *content);
void		ft_lstadd_back(t_list **lst, t_list *newelem);
int			ft_strcmp(const char *s1, const char *s2);
const char	*ft_strchr(const char *str, char c);
int			apply_all_redir(t_ctx *ctx, t_list_redir *it_redir);
void		end(t_ctx *ctx, t_full_cmd *cmd);
int			simple_atoi(int *ptr_to_n, const char *str);
int			put_str_fd(const char *s, int fd);
// Builtin commands implemented:
int			bi_echo(char **argv, t_ctx *ctx);
int			bi_cd(char **argv, t_ctx *ctx);
int			bi_pwd(char **argv, t_ctx *ctx);
int			bi_export(char **argv, t_ctx *ctx);
int			bi_unset(char **argv, t_ctx *ctx);
int			bi_env(char **argv, t_ctx *ctx);
int			bi_exit(char **argv, t_ctx *ctx);

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
	err += add_one_bi("cd", &bi_cd, builtins);
	err += add_one_bi("pwd", &bi_pwd, builtins);
	err += add_one_bi("export", &bi_export, builtins);
	err += add_one_bi("unset", &bi_unset, builtins);
	err += add_one_bi("env", &bi_env, builtins);
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

/*
◦ exit with no options

exit 
Exit the shell, returning a status of n to the shell’s parent. If n is omitted, 
	the exit status is that of the last command executed.
*/
int	exec_bi(t_single_cmd *s_cmd, t_ctx *ctx, t_full_cmd *f_c, int sub)
{
	int	ret;

	if (sub)
	{
		ret = (*s_cmd->builtin->ft)(s_cmd->argv, ctx);
		end (ctx, f_c);
		exit (ret);
	}
	else
	{
		if (apply_all_redir(ctx, s_cmd->redir))
			return (1);
		ret = (*s_cmd->builtin->ft)(s_cmd->argv, ctx);
		ctx->exit_status = ret;
		if (dup2(ctx->fd_stdin, 0) < 0)
			return (perror("dup2 in exec_bi"), 1);
		if (dup2(ctx->fd_stdout, 1) < 0)
			return (perror("dup2 in exec_bi"), 1);
		if (ft_strcmp(s_cmd->builtin->name, "exit") == 0)
		{
			end(ctx, f_c);
			exit(ret);
		}
	}
	return (0);
}

int	bi_exit(char **argv, t_ctx *ctx)
{
	int	n;

	argv++;
	if (*argv)
	{
		if (simple_atoi(&n, *argv))
		{
			put_str_fd("minishell: exit: ", 2);
			put_str_fd(*argv, 2);
			put_str_fd(": numeric argument required\n", 2);
			return (2);
		}
		if (argv[1])
			return (put_str_fd("minishell: exit: too many arguments\n", 2), 1);
		return (n % 256);
	}
	return (ctx->exit_status);
}
