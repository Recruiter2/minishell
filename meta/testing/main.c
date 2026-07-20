/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 15:48:35 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/20 21:09:03 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/prepare_execution.h"
#include <stdio.h>

char	**ft_split(char const *s, char c);
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

	char	*name;
	char	*value;

	(void)argc;
	(void)argv;
	// This transfers the information about the environment to ctx
	// For the time being it is mostly about the PATH
	if (init_ctx(&ctx, envp))
		return (1);
	printf("debug signal 0\n");
	
	// example to run: < txt.txt grep et | wc -l > out.txt
	if (1)
	{
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
		destroy_cmd(&full_cmd);
		// we free the ressources used to create the two argv 
		free_all(&first_cmd);
		free_all(&second_cmd);
	}
	// example to run: < txt.txt tail --lines=5 | grep et | wc -l >> out.txt
	if (1)
	{
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
		destroy_cmd(&full_cmd);
		free_all(&first_cmd);
		free_all(&second_cmd);
		free_all(&third_cmd);
	}
	// example to run: < txt.txt << END grep hi | wc -l > out2.txt >> out.txt
	if (0)
	{
		full_cmd = initialize_cmd();
		add_file_in(full_cmd, "txt.txt");
		add_here_doc(full_cmd, "END");
		first_cmd = ft_split("grep hi", ' ');
		add_single_cmd(full_cmd, first_cmd);
		second_cmd = ft_split("wc -l", ' ');
		add_single_cmd(full_cmd, second_cmd);
		add_file_out(full_cmd, "out2.txt", 0);
		add_file_out(full_cmd, "out.txt", 1);
		execute_cmd(&ctx, full_cmd);
		destroy_cmd(&full_cmd);
		free_all(&first_cmd);
		free_all(&second_cmd);
	}
	if (1)
	{
		full_cmd = initialize_cmd();
		first_cmd = ft_split("cat -e txt.txt", ' ');
		add_single_cmd(full_cmd, first_cmd);
		// add_file_in(full_cmd, "txt.txt");
		execute_cmd(&ctx, full_cmd);
		printf("debug signal 21\n");
		destroy_cmd(&full_cmd);
		free_all(&first_cmd);
	}
	// example to run: echo hi ha hu "1 2 3"
	if (1)
	{
		full_cmd = initialize_cmd();
		first_cmd = ft_split("echo hi", ' ');
		add_single_cmd(full_cmd, first_cmd);
		execute_cmd(&ctx, full_cmd);
		printf("debug signal 20\n");
		destroy_cmd(&full_cmd);
		free_all(&first_cmd);
	}
	if (1)
	{
		name = "USER";
		value = evar_expansion(&ctx, name);
		printf("%s=%s\n", name, value);
		name = "LANG";
		value = evar_expansion(&ctx, name);
		printf("%s=%s\n", name, value);
		name = "USER";
		value = evar_expansion(&ctx, name);
		printf("%s=%s\n", name, value);	
	}

	// finish clean up
	free_ctx_ressources(&ctx);
}