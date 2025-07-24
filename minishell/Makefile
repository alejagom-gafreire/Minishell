# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gafreire <gafreire@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/07/22 19:27:35 by alejogogi         #+#    #+#              #
#    Updated: 2025/07/24 18:17:39 by gafreire         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = main.c prompt.c lexer.c parcer.c lexer_quotes.c
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
