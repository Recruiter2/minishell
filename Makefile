NAME		= minishell
CC			= cc
CFLAGS		= -Wall -Werror -Wextra -Wpedantic -g #remove last two flags before vogosphere
SRC_DIR 	= src
OBJ_DIR 	= obj
LIBFT_DIR	= Libft 
INC_DIR 	= includes
INCLUDES	= -I$(INC_DIR) -I$(LIBFT_DIR)
LIBFT		= $(LIBFT_DIR)/libft.a

SRCS 		= 	main.c\
				user_input.c\
				history.c\
				signaling.c\
				lexer.c\
				lexer_fts.c\
				lexer_functions.c\
				lexer_pipe_redir.c\
				dispatcher_helper.c\
				dispatcher_lib.c\
				dispatcher.c\
				handle_expansion.c\
				executor/prepare_cmd.c\
				executor/prepare_redirections.c\
				executor/environment.c\
				executor/path.c\
				executor/redirections.c\
				executor/builtins_ctx_exit.c\
				executor/builtins_echo_cd_pwd_unset.c\
				executor/builtins_env_export.c\
				executor/exec.c\
				executor/clean_up.c\
				utils/lists1.c\
				utils/lists2.c\
				utils/get_next_line.c\
				utils/ft_split.c\
				utils/exec_utils1.c\
				utils/exec_utils2.c\

OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))


all: $(NAME)

$(LIBFT):
	make -C $(LIBFT_DIR)

$(NAME): $(OBJS) $(LIBFT) 
	$(CC) $(OBJS) -L$(LIBFT_DIR) -lft -lreadline -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)/executor
	@mkdir -p $(OBJ_DIR)/utils
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	rm -rf $(NAME)
	make -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
