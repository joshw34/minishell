NAME = libft.a

C_FILES =	./functions/part_1/ft_atoi.c \
			./functions/part_1/ft_bzero.c \
			./functions/part_1/ft_calloc.c \
			./functions/part_1/ft_isalnum.c \
			./functions/part_1/ft_isalpha.c \
			./functions/part_1/ft_isascii.c \
			./functions/part_1/ft_isdigit.c \
			./functions/part_1/ft_isprint.c \
			./functions/part_1/ft_memchr.c \
			./functions/part_1/ft_memcmp.c \
			./functions/part_1/ft_memcpy.c \
			./functions/part_1/ft_memmove.c \
			./functions/part_1/ft_memset.c \
			./functions/part_1/ft_strchr.c \
			./functions/part_1/ft_strdup.c \
			./functions/part_1/ft_strlcat.c \
			./functions/part_1/ft_strlcpy.c \
			./functions/part_1/ft_strlen.c \
			./functions/part_1/ft_strncmp.c \
			./functions/part_1/ft_strnstr.c \
			./functions/part_1/ft_strrchr.c \
			./functions/part_1/ft_tolower.c \
			./functions/part_1/ft_toupper.c \
			./functions/part_2/ft_itoa.c \
			./functions/part_2/ft_putchar_fd.c \
			./functions/part_2/ft_putendl_fd.c \
			./functions/part_2/ft_putnbr_fd.c \
			./functions/part_2/ft_putstr_fd.c \
			./functions/part_2/ft_split.c \
			./functions/part_2/ft_striteri.c \
			./functions/part_2/ft_strjoin.c \
			./functions/part_2/ft_strmapi.c \
			./functions/part_2/ft_strtrim.c \
			./functions/part_2/ft_substr.c \
			./functions/part_3_bonus/ft_lstadd_back_bonus.c \
			./functions/part_3_bonus/ft_lstadd_front_bonus.c \
			./functions/part_3_bonus/ft_lstclear_bonus.c \
			./functions/part_3_bonus/ft_lstdelone_bonus.c \
			./functions/part_3_bonus/ft_lstiter_bonus.c \
			./functions/part_3_bonus/ft_lstlast_bonus.c \
			./functions/part_3_bonus/ft_lstmap_bonus.c \
			./functions/part_3_bonus/ft_lstnew_bonus.c \
			./functions/part_3_bonus/ft_lstsize_bonus.c \
			./functions/ft_printf/ft_printf.c \
			./functions/ft_printf/print_dec.c \
			./functions/ft_printf/print_hex.c \
			./functions/ft_printf/print_ptr.c \
			./functions/ft_printf/print_text.c \
			./functions/get_next_line/get_next_line.c \
			./functions/get_next_line/get_next_line_utils.c \

OBJ_FILES = $(C_FILES:.c=.o)

REMOVE = rm -f
CC = cc
CFLAGS = -Wall -Werror -Wextra -Wno-unused-result

all: $(NAME)

libft:	all

$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $(OBJ_FILES)
	@echo "Libft:	Library Created"

.c.o:
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(REMOVE) $(OBJ_FILES)
	@echo "Libft:	Object Files Removed"

fclean:	
	@$(REMOVE) $(OBJ_FILES)
	@echo "Libft:	Object Files Removed"
	@$(REMOVE) $(NAME)
	@echo "Libft:	Library Removed"

re:	fclean all

.PHONY: all clean fclean re
