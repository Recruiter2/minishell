/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/04 00:29:04 by tzinaliy          #+#    #+#             */
/*   Updated: 2026/06/04 13:19:27 by tzinaliy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <readline/history.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../Libft/libft.h"

//function for user input or parsing...
// this function check if readline is empty
int is_blank(const char *s);
void	handle_input(void);

// history functions
void add_shell_history(const char *line);
void builtin_history(void);
