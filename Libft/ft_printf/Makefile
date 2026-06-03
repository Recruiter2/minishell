# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tzinaliy <tzinaliy@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/13 21:14:27 by tzinaliy          #+#    #+#              #
#    Updated: 2026/06/04 00:38:16 by tzinaliy         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
CC:= cc
CFLAGS := -Wall -Wextra -Werror

CFILES := ft_hex_low.c ft_hex_upper.c ft_putchar.c ft_putnbr.c\
		ft_putstr.c ft_printf.c ft_put_us_int.c ft_putptr.c

OBJ_DIR = obj

ERRORFILES := ft_printf.h.gch a.out
AR := ar rcs
#OFILES	:= $(CFILES:.c=.o)
OFILES = $(addprefix $(OBJ_DIR)/, $(CFILES:.c=.o))

$(OBJ_DIR)/%.o: %.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME) 

$(NAME) : $(OFILES) 
		@$(AR) $(NAME) $(OFILES)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
#$(OBJ_DIR)/%.o: %.c 
#	mkdir -p $(OBJ_DIR)
#	@$(CC) $(CFLAGS) -c $< -o $@

clean:
		rm -rf $(OBJ_DIR)
		@rm -f $(OFILES) $(ERRORFILES)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
