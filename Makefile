NAME         = minishell

CC             = cc
CFLAGS         = -Wall -Werror -Wextra -g

INCLUDES = -I$(INC_DIR) -I$(LIBFT_DIR)

READLINE_LIBS = -lreadline 
LIBFT_DIR    = Libft 
LIBFT         = $(LIBFT_DIR)/libft.a

FT_PRINTF_PATH := Libft/ft_printf
FT_PRINTF := -L ${FT_PRINTF_PATH} -lftprintf


SRC_DIR = src
OBJ_DIR = obj
INC_DIR = includes

SRCS = 	main.c\
		user_input.c\
		history.c\
		signaling.c\
		lexer.c\
		lexer_fts.c\
		lexer_functions.c\
		lexer_pipe_redir.c\
		redirections.c\
		prepare_cmd.c\
		path.c\
		lists.c\
		get_next_line.c\
		ft_split.c\
		exec_utils.c\
		exec.c\
		clean_up.c\
		dispatcher_helper.c\
		dispatcher.c\





OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))


all:  $(LIBFT) $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)



$(NAME):  $(OBJS)
	make -C Libft/ft_printf all
	$(CC) -no-pie $(OBJS) -L$(LIBFT_DIR) -lft ${FT_PRINTF} $(READLINE_LIBS) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	rm -f *.o 
	make -C $(LIBFT_DIR) clean
	make -C ./Libft/ft_printf clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean
	make -C ./Libft/ft_printf fclean

re: fclean all

.PHONY: all clean fclean re
