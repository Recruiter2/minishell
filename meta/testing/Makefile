# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marhuber <marhuber@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/06/06 16:56:26 by marhuber          #+#    #+#              #
#    Updated: 2026/07/17 16:41:12 by marhuber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Names of the executables
NAME = test

# Compiling
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Name of all sources files to be passed to the CC command
MY_SOURCES = main.c \
	../../src/executor/exec.c \
	../../src/executor/path.c \
	../../src/executor/prepare_cmd.c \
	../../src/executor/clean_up.c \
	../../src/executor/redirections.c \
	../../src/utils/lists.c \
	../../src/utils/get_next_line.c \
	../../src/utils/exec_utils.c \
	../../src/utils/ft_split.c 

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