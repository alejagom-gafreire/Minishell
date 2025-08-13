# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 19:27:35 by alejogogi         #+#    #+#              #
#    Updated: 2025/08/12 15:44:25 by gafreire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 19:27:35 by alejogogi         #+#    #+#              #
#    Updated: 2025/08/06 16:59:25 by gafreire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 19:27:35 by alejogogi         #+#    #+#              #
#    Updated: 2025/08/06 16:59:25 by gafreire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc

# Flags de compilación
CFLAGS = -Wall -Werror -Wextra -I./include -I./libft -g3
SANITIZE = -fsanitize=address,leak,undefined

# Flags de linkeo
LDFLAGS = $(SANITIZE)
LDLIBS = -lreadline

SRC = \
	src/main.c \
	src/signals/signals.c \
	src/prompt/prompt.c \
	src/lexer/lexer.c \
	src/parser/parcer.c \
	src/parser/parcer_aux.c \
	src/parser/check_parcer_handle.c\
	src/lexer/lexer_quotes.c \
	src/lexer/check_handles.c \
	src/lexer/check_operators.c \
	src/expander/expander_write.c \
	src/expander/expander.c \
	src/expander/expander_utils.c \
	src/expander/expander_status.c \
	src/expander/expander_tokens.c \
	src/expander/expander_check.c \
	src/utils/prints.c \
	src/execute/execute.c \
	src/execute/execute_aux.c \
	src/execute/proccess_execve.c \
	src/utils/ft_free.c

OBJ = $(SRC:.c=.o)

RM = rm -f

LIB_DIR = ./libft
LIBFT = $(LIB_DIR)/libft.a

.PHONY: all clean fclean re

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIB_DIR)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME) $(LDFLAGS) $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) $(SANITIZE) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all

# NAME = minishell
# CC = cc
# CFLAGS = -Wall -Werror -Wextra -I./include -I./libft -g3 -fsanitize=address,leak,undefined

# SRC = \
# 	src/main.c \
# 	src/prompt/prompt.c \
# 	src/lexer/lexer.c \
# 	src/parser/parcer.c \
# 	src/parser/parcer_aux.c \
# 	src/lexer/lexer_quotes.c \
# 	src/lexer/check_handles.c \
# 	src/lexer/check_operators.c \
# 	src/utils/prints.c \
# 	src/execute/pipex_aux.c\
# 	src/execute/one_cmd.c\
# 	src/utils/ft_free.c
# OBJ = $(SRC:.c=.o)
# RM = rm -f

# LIB_DIR = ./libft
# LIBFT = $(LIB_DIR)/libft.a

# LIBFT_INCLUDE = libft

# .PHONY: all clean fclean re

# all: $(NAME) $(LIBFT)

# $(LIBFT):
# 	$(MAKE)	-C $(LIB_DIR)
	
# $(NAME): $(OBJ) $(LIBFT)
# 	$(CC) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	$(RM) $(OBJ)
# 	$(MAKE) -C $(LIB_DIR) clean

# fclean: clean
# 	$(RM) $(NAME)
# 	$(MAKE) -C $(LIB_DIR) fclean

# re: fclean all
