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

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra -I./include -I./libft
SRC = \
	src/main.c \
	src/signals/signals.c \
	src/prompt/prompt.c \
	src/lexer/lexer.c \
	src/parser/parcer.c \
	src/parser/parcer_aux.c \
	src/lexer/lexer_quotes.c \
	src/lexer/check_handles.c \
	src/lexer/check_operators.c \
	src/utils/prints.c \
	src/execute/pipex.c\
	src/execute/pipex_aux.c\
	src/utils/ft_free.c
OBJ = $(SRC:.c=.o)
RM = rm -f

LIB_DIR = ./libft
LIBFT = $(LIB_DIR)/libft.a

LIBFT_INCLUDE = libft

.PHONY: all clean fclean re

all: $(NAME) $(LIBFT)

$(LIBFT):
	$(MAKE)	-C $(LIB_DIR)
	
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(LIBFT) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(MAKE) -C $(LIB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIB_DIR) fclean

re: fclean all
