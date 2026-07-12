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
		dispatcher.c\
		misc.c\
		executor/redirections.c\
		executor/prepare_cmd.c\
		executor/path.c\
		executor/lists.c\
		executor/get_next_line.c\
		executor/ft_split.c\
		executor/exec_utils.c\
		executor/exec.c\
		executor/clean_up.c\




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
