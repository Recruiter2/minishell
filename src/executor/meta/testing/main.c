/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:48:35 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/06 09:34:27 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../prepare_execution.h"

char	**ft_split(char const *s, char c);
void	end(t_ctx *ctx, t_full_cmd *cmd);
void	free_all(char ***strs);


int	main(int argc, char **argv, char **envp)
{
	// This object saves information about the context that is valid all the time
	t_ctx		ctx;		
	// Objects of this type save the information about one line of user input
	t_full_cmd	*full_cmd;
	// Objects of this type are the argv of one simple command
	// e.g. fist_cmd[0] is the executable, first_cmd[1] is the first argument, ...
	char	**first_cmd;
	char	**second_cmd;
	char	**third_cmd;

	argc = 0;
	argc++;
	**argv = 0;
	// This transfers the information about the environment to ctx
	// For the time being it is mostly about the PATH
	if (read_envp(envp, &ctx))
		return (1);
	
	// example to run: < txt.txt grep et | wc -l > out.txt

	// first we create an instance of t_full_cmd named full_cmd
	// at the beginning this is just and empty container
	full_cmd = initialize_cmd();
	// we add a redirection to full_cmd
	add_file_in(full_cmd, "txt.txt");
	// we create an argv for "grep et"
	first_cmd = ft_split("grep et", ' ');
	// we add this argv to full_cmd
	add_single_cmd(full_cmd, first_cmd);
	// the same for "wc -l"
	second_cmd = ft_split("wc -l", ' ');
	add_single_cmd(full_cmd, second_cmd);
	// we add another redirection
	add_file_out(full_cmd, "out.txt", 0);
	// now all the information in "< txt.txt grep et | wc -l > out.txt" is linked with full_cmd

	// we ask the executor to execute full_cmd
	execute_cmd(&ctx, full_cmd);
	// we free the ressources used to set up full_cmd
	destroy(&full_cmd);
	// we free the ressources used to create the two argv 
	free_all(&first_cmd);
	free_all(&second_cmd);
	// example to run: < txt.txt tail --lines=5 | grep et | wc -l >> out.txt
	full_cmd = initialize_cmd();
	add_file_in(full_cmd, "txt.txt");
	first_cmd = ft_split("tail --lines=5", ' ');
	add_single_cmd(full_cmd, first_cmd);
	second_cmd = ft_split("grep et", ' ');
	add_single_cmd(full_cmd, second_cmd);
	third_cmd = ft_split("wc -l", ' ');
	add_single_cmd(full_cmd, third_cmd);
	add_file_out(full_cmd, "out.txt", 1);
	execute_cmd(&ctx, full_cmd);
	destroy(&full_cmd);
	free_all(&first_cmd);
	free_all(&second_cmd);
	free_all(&third_cmd);
	// example to run: < txt.txt << END grep ipsum | wc -l > out2.txt >> out.txt
	full_cmd = initialize_cmd();
	add_file_in(full_cmd, "txt.txt");
	add_here_doc(full_cmd, "END");
	first_cmd = ft_split("grep ipsum", ' ');
	add_single_cmd(full_cmd, first_cmd);
	second_cmd = ft_split("wc -l", ' ');
	add_single_cmd(full_cmd, second_cmd);
	add_file_out(full_cmd, "out2.txt", 0);
	add_file_out(full_cmd, "out.txt", 1);
	execute_cmd(&ctx, full_cmd);
	destroy(&full_cmd);
	free_all(&first_cmd);
	free_all(&second_cmd);
	// finish clean up
	free_all(&ctx.path);
}