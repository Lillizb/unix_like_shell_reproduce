#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: chris <chris@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/14 12:35:11 by cwick             #+#    #+#              #
#    Updated: 2024/09/12 15:18:50 by chris            ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = minishell

SRC = $(wildcard *.c)
SRC_LEXER = $(wildcard $(LEXER)/*.c)
SRC_PARSER = $(wildcard $(PARSER)/*.c)
SRC_BUILTINS = $(wildcard $(BUILTINS)/*.c)
SRC_ENV = $(wildcard $(ENVP)/*.c)
SRC_UTILS = $(wildcard $(UTILS)/*.c)
SRC_GNL = $(wildcard $(GNL)/*.c)
SRC_EXE = $(wildcard $(EXE)/*.c)
SRC_REDIR = $(wildcard $(REDIR)/*.c)

OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
OBJ_LEXER = $(patsubst $(LEXER)/%.c, $(LEXER)/$(OBJ_DIR)/%.o, $(SRC_LEXER))
OBJ_PARSER = $(patsubst $(PARSER)/%.c, $(PARSER)/$(OBJ_DIR)/%.o, $(SRC_PARSER))
OBJ_BUILTINS = $(patsubst $(BUILTINS)/%.c, $(BUILTINS)/$(OBJ_DIR)/%.o, $(SRC_BUILTINS))
OBJ_ENV = $(patsubst $(ENVP)/%.c, $(ENVP)/$(OBJ_DIR)/%.o, $(SRC_ENV))
OBJ_UTILS = $(patsubst $(UTILS)/%.c, $(UTILS)/$(OBJ_DIR)/%.o, $(SRC_UTILS))
OBJ_GNL = $(patsubst $(GNL)/%.c, $(GNL)/$(OBJ_DIR)/%.o, $(SRC_GNL))
OBJ_EXE = $(patsubst $(EXE)/%.c, $(EXE)/$(OBJ_DIR)/%.o, $(SRC_EXE))
OBJ_REDIR = $(patsubst $(REDIR)/%.c, $(REDIR)/$(OBJ_DIR)/%.o, $(SRC_REDIR))

LIBFT = libft/libft.a
TOKEN_LIST = token_list/tokenlist.a
OBJ_DIR = obj_dir
LEXER = lexer
PARSER = parser
BUILTINS = builtins
ENVP = envp
UTILS = utils
GNL = get_next_line
EXE = executor
REDIR = redir
MKDIR = mkdir -p

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LFLAGS = -lreadline			#linker flags

all: $(NAME)

$(NAME): $(OBJ) $(OBJ_LEXER) $(OBJ_PARSER) $(OBJ_BUILTINS) $(OBJ_ENV) $(OBJ_UTILS) $(OBJ_GNL) $(OBJ_EXE) $(OBJ_REDIR) $(LIBFT) $(TOKEN_LIST)
	$(CC) $(OBJ) $(OBJ_LEXER) $(OBJ_PARSER) $(OBJ_BUILTINS) $(OBJ_ENV) $(OBJ_UTILS) $(OBJ_GNL) $(OBJ_EXE) $(OBJ_REDIR) $(LIBFT) $(TOKEN_LIST) -o $(NAME) $(LFLAGS)

$(OBJ_DIR)/%.o:%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(LEXER)/$(OBJ_DIR)/%.o: $(LEXER)/%.c | $(LEXER)/$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(PARSER)/$(OBJ_DIR)/%.o: $(PARSER)/%.c | $(PARSER)/$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(BUILTINS)/$(OBJ_DIR)/%.o: $(BUILTINS)/%.c | $(BUILTINS)/$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(ENVP)/$(OBJ_DIR)/%.o: $(ENVP)/%.c | $(ENVP)/$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(UTILS)/$(OBJ_DIR)/%.o: $(UTILS)/%.c | $(UTILS)/$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(GNL)/$(OBJ_DIR)/%.o: $(GNL)/%.c | $(GNL)/$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(EXE)/$(OBJ_DIR)/%.o: $(EXE)/%.c | $(EXE)/$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(REDIR)/$(OBJ_DIR)/%.o: $(REDIR)/%.c | $(REDIR)/$(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	$(MKDIR) $(OBJ_DIR)

$(LEXER)/$(OBJ_DIR):
	$(MKDIR) $(LEXER)/$(OBJ_DIR)

$(PARSER)/$(OBJ_DIR):
	$(MKDIR) $(PARSER)/$(OBJ_DIR)

$(BUILTINS)/$(OBJ_DIR):
	$(MKDIR) $(BUILTINS)/$(OBJ_DIR)

$(ENVP)/$(OBJ_DIR):
	$(MKDIR) $(ENVP)/$(OBJ_DIR)

$(UTILS)/$(OBJ_DIR):
	$(MKDIR) $(UTILS)/$(OBJ_DIR)

$(GNL)/$(OBJ_DIR):
	$(MKDIR) $(GNL)/$(OBJ_DIR)

$(EXE)/$(OBJ_DIR):
	$(MKDIR) $(EXE)/$(OBJ_DIR)

$(REDIR)/$(OBJ_DIR):
	$(MKDIR) $(REDIR)/$(OBJ_DIR)

$(LIBFT):
	$(MAKE) -C libft

 $(TOKEN_LIST):
	$(MAKE) -C token_list

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(LEXER)/$(OBJ_DIR)
	rm -rf $(PARSER)/$(OBJ_DIR)
	rm -rf $(BUILTINS)/$(OBJ_DIR)
	rm -rf $(ENVP)/$(OBJ_DIR)
	rm -rf $(UTILS)/$(OBJ_DIR)
	rm -rf $(GNL)/$(OBJ_DIR)
	rm -rf $(EXE)/$(OBJ_DIR)
	rm -rf $(REDIR)/$(OBJ_DIR)
	$(MAKE) -C libft clean
	$(MAKE) -C token_list clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean
	$(MAKE) -C token_list fclean

re: fclean all

.PHONY: all clean fclean re
