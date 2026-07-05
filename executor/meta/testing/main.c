/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:48:35 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/05 12:04:38 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../prepare_execution.h"

char	**ft_split(char const *s, char c);
void	end(t_ctx *ctx, t_full_cmd *cmd);
void	free_all(char ***strs);


int	main(int argc, char **argv, char **envp)
{
	t_ctx		ctx;
	t_full_cmd	*cmd;
	char	**first_cmd;
	char	**second_cmd;
	char	**third_cmd;

	argc = 0;
	argc++;
	**argv = 0;
	if (read_envp(envp, &ctx))
		return (1);
	// example to run: < txt.txt grep et | wc -l > out.txt
	cmd = initialize_cmd();
	add_file_in(cmd, "txt.txt");
	first_cmd = ft_split("grep et", ' ');
	add_single_cmd(cmd, first_cmd);
	second_cmd = ft_split("wc -l", ' ');
	add_single_cmd(cmd, second_cmd);
	add_file_out(cmd, "out.txt", 0);
	execute_cmd(&ctx, cmd);
	destroy(&cmd);
	free_all(&first_cmd);
	free_all(&second_cmd);
	// example to run: < txt.txt tail --lines=5 | grep et | wc -l >> out.txt
	cmd = initialize_cmd();
	add_file_in(cmd, "txt.txt");
	first_cmd = ft_split("tail --lines=5", ' ');
	add_single_cmd(cmd, first_cmd);
	second_cmd = ft_split("grep et", ' ');
	add_single_cmd(cmd, second_cmd);
	third_cmd = ft_split("wc -l", ' ');
	add_single_cmd(cmd, third_cmd);
	add_file_out(cmd, "out.txt", 1);
	execute_cmd(&ctx, cmd);
	destroy(&cmd);
	free_all(&first_cmd);
	free_all(&second_cmd);
	free_all(&third_cmd);
	// example to run: < txt.txt << END grep ipsum | wc -l > out2.txt >> out.txt
	cmd = initialize_cmd();
	add_file_in(cmd, "txt.txt");
	add_here_doc(cmd, "END");
	first_cmd = ft_split("grep ipsum", ' ');
	add_single_cmd(cmd, first_cmd);
	second_cmd = ft_split("wc -l", ' ');
	add_single_cmd(cmd, second_cmd);
	add_file_out(cmd, "out2.txt", 0);
	add_file_out(cmd, "out.txt", 1);
	execute_cmd(&ctx, cmd);
	destroy(&cmd);
	free_all(&first_cmd);
	free_all(&second_cmd);
	// finish clean up
	free_all(&ctx.path);
}