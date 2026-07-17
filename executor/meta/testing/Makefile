# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/06 16:56:26 by marhuber          #+#    #+#              #
#    Updated: 2026/07/16 18:41:51 by marhuber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Names of the executables
NAME = test

# Compiling
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Name of all sources files to be passed to the CC command
MY_SOURCES = main.c ../../exec_utils.c ../../exec.c ../../ft_split.c \
	../../path.c ../../get_next_line.c ../../prepare_cmd.c ../../clean_up.c \
	../../redirections.c ../../lists.c ../../builtins1.c ../../environment.c

MY_OBJECTS = $(MY_SOURCES:.c=.o)

## Rules to compile
# Rule that gets called by default 
$(NAME): $(MY_OBJECTS) 
	$(CC) $^ -o $(NAME) 
# An implicit rule creates the objects using CFLAGS

all: $(NAME)

## Rules to clean up
clean:
	rm -f $(MY_OBJECTS)

fclean: clean
	rm -f $(NAME)
	
re: fclean all

.SECONDARY: $(MY_OBJECTS)