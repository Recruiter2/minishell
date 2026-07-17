/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_execution.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/06 14:43:34 by marhuber          #+#    #+#             */
/*   Updated: 2026/07/15 18:40:35 by marhuber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PREPARE_EXECUTION_H
# define PREPARE_EXECUTION_H

# include "executor.h"

// External functions (used to communicate to the executor)

// Set up & destroy context variable

/**
* Initializes an instance of t_ctx to use across the entire programm
* @param ctx will point at the instance to be initialized
* @param envp must be the same as in main(argc, arv, envp)
*/
int			init_ctx(t_ctx *ctx, char **envp);
void		free_ctx_ressources(t_ctx *ctx);

// Expand environment variables
char		*evar_expansion(char *name);

// Prepare command structure for the executor, execute and destroz structure
t_full_cmd	*initialize_cmd(void);
int			add_file_in(t_full_cmd *cmd, char *filename);
int			add_here_doc(t_full_cmd *cmd, char *delimiter);
int			add_file_out(t_full_cmd *cmd, char *filename, int append);
int			add_single_cmd(t_full_cmd *cmd, char **argv);
int			execute_cmd(t_ctx *ctx, t_full_cmd *cmd);
void		destroy_cmd(t_full_cmd **ptrcmd);

#endif