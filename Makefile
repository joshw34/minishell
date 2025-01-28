NAME = minishell

SRC_DIR = ./src
INC_DIR = ./inc
LIBFT_DIR = ./libft

LIBFT = $(LIBFT_DIR)/libft.a

SRC_FILES =	$(SRC_DIR)/main.c \
			$(SRC_DIR)/init_data_struct.c \
			$(SRC_DIR)/get_input.c \
			$(SRC_DIR)/process_user_input.c \
			$(SRC_DIR)/token_splitter.c \
			$(SRC_DIR)/token_expand.c \
			$(SRC_DIR)/token_syntax.c \
			$(SRC_DIR)/token_expand_utils.c \
			$(SRC_DIR)/token_str_join.c \
			$(SRC_DIR)/token_list.c \
			$(SRC_DIR)/token_utils.c \
			$(SRC_DIR)/token_process_heredoc.c \
			$(SRC_DIR)/token_heredoc_insert_var.c \
			$(SRC_DIR)/cmd_list.c \
			$(SRC_DIR)/cmd_list_utils.c \
			$(SRC_DIR)/cmd_list_parse_args.c \
			$(SRC_DIR)/redir_list.c \
			$(SRC_DIR)/free.c \
			$(SRC_DIR)/free_list_clear.c \
			$(SRC_DIR)/signal_handling.c \
			$(SRC_DIR)/builtin_cd.c \
			$(SRC_DIR)/builtin_cd_utils.c \
			$(SRC_DIR)/builtin_echo.c \
			$(SRC_DIR)/builtin_execution_handling.c \
			$(SRC_DIR)/builtin_exit.c \
			$(SRC_DIR)/builtin_pwd.c \
			$(SRC_DIR)/builtin_var_export.c \
			$(SRC_DIR)/builtin_var_export_2.c \
			$(SRC_DIR)/builtin_var_export_utils.c \
			$(SRC_DIR)/builtin_var_get_print.c \
			$(SRC_DIR)/builtin_var_utils.c \
			$(SRC_DIR)/check_builtins.c \
			$(SRC_DIR)/utils.c \
			$(SRC_DIR)/execution_handling.c \
			$(SRC_DIR)/fetch_path_command.c \
			$(SRC_DIR)/multi_processing_handling.c \
			$(SRC_DIR)/redirection_file_opening.c \
			$(SRC_DIR)/redirection_handling.c \
			$(SRC_DIR)/DEBUG_FUNCS.c \

OBJ_FILES = $(SRC_FILES:.c=.o)

REMOVE = rm -f
CC = clang
CFLAGS = -Wall -Werror -Wextra -I$(INC_DIR) -I$(LIBFT_DIR)
LDFLAGS = -lreadline -lhistory

all: $(NAME)

$(NAME): $(LIBFT) $(OBJ_FILES)
	@echo "Compiling/Linking"
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LDFLAGS) $(LIBFT) -o $(NAME)
	@echo "Ready"

$(LIBFT):
	@echo "Libft: Compiling"
	@make -s all -C $(LIBFT_DIR)
	
.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@make -s clean -C $(LIBFT_DIR)
	@echo "Removing .o files"
	@$(REMOVE) $(OBJ_FILES)

fclean:	clean
	@make -s fclean -C $(LIBFT_DIR)
	@echo "Removing executable"
	@$(REMOVE) $(NAME)

re:	fclean all

.PHONY: all clean fclean re
