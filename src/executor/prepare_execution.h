/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:43:34 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/05 12:37:38 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPARE_EXECUTION_H
# define PREPARE_EXECUTION_H

# include <unistd.h>
# include "executor.h"

// External types (used to communicate to the executor)

typedef struct s_contextual_information
{
	char	**path;			// array of strings containing directories in PATH
	char	**envp;
}			t_ctx;

int			read_envp(char **envp, t_ctx *ctx);
t_full_cmd	*initialize_cmd(void);
int			add_file_in(t_full_cmd *cmd, char *filename);
int			add_here_doc(t_full_cmd *cmd, char *delimiter);
int			add_file_out(t_full_cmd *cmd, char *filename, int append);
int			add_single_cmd(t_full_cmd *cmd, char **argv);
int			execute_cmd(t_ctx *ctx, t_full_cmd *cmd);
void		destroy(t_full_cmd **ptrcmd);

#endif

/*
// Minimal usage example

char	**ft_split(char const *s, char c);

int	main(int argc, char **argv, char **envp)
{
	t_ctx ctx;
	t_full_cmd *cmd;

	argc = 0;
	argc++;
	**argv = 0;
	if (read_envp(envp, &ctx))
		return (1);
	// example to run: < txt.txt grep et | wc -l > out.txt
	cmd = initialize_cmd();
	add_file_in(cmd, "txt.txt");
	add_single_cmd(cmd, ft_split("grep et", ' '));
	add_single_cmd(cmd, ft_split("wc - l", ' '));
	add_file_out(cmd, "out.txt", 0);
	execute_cmd(&ctx, cmd);
	destroy(cmd);
}
*/