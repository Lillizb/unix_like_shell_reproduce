
NAME = libft.a

SRC = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
	ft_memcpy.c ft_memmove.c ft_memset.c ft_strchr.c ft_strlcat.c ft_strlcpy.c \
	ft_strlen.c ft_tolower.c ft_toupper.c ft_strrchr.c ft_strcmp.c ft_strncmp.c ft_atoi.c ft_memchr.c \
	ft_memcmp.c ft_strnstr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
	ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c \
	ft_striteri.c ft_split.c

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
OBJ_DIR = obj_dir
MKDIR = mkdir -p

all: $(NAME)

$(NAME): $(OBJ)
	ar rcs $@ $^

$(OBJ_DIR)/%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
