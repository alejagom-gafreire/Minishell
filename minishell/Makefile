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

# Flags de compilación
CFLAGS = -Wall -Werror -Wextra -I./include -I./libft -g3


# Flags de linkeo

LDLIBS = -lreadline

SRC = \
	src/main.c \
	src/signals/signals.c \
	src/prompt/prompt.c \
	src/prompt/aux_prompt.c \
	src/prompt/utils_prompt.c \
	src/prompt/prompt_create.c \
	src/lexer/lexer.c \
	src/parcer/parcer.c \
	src/parcer/parcer_aux.c \
	src/parcer/check_parcer_handle.c\
	src/parcer/check_redirection.c\
	src/lexer/lexer_quotes.c \
	src/lexer/check_handles.c \
	src/lexer/aux_handler.c \
	src/lexer/check_operators.c \
	src/expander/expander_write.c \
	src/expander/expander.c \
	src/expander/expander_utils.c \
	src/expander/expander_status.c \
	src/expander/expander_tokens.c \
	src/expander/expander_check.c \
	src/expander/expander_vars.c \
	src/expander/expander_split/expander_split.c \
	src/expander/expander_split/expander_split_tokens.c \
	src/expander/expander_split/expander_split_utils.c \
	src/utils/prints.c \
	src/execute/execute.c \
	src/execute/execute_aux.c \
	src/execute/proccess_execve.c \
	src/execute/procces_execve_aux.c \
	src/execute/execute_child.c \
	src/utils/ft_free.c\
	src/built-ins/built-ins.c\
	src/built-ins/ft_exit.c \
	src/built-ins/ft_cd/ft_cd.c \
	src/built-ins/ft_cd/cd_aux.c \
	src/built-ins/ft_echo.c \
	src/built-ins/ft_pwd.c \
	src/built-ins/ft_env.c \
	src/built-ins/ft_export.c \
	src/built-ins/aux_export.c \
	src/built-ins/ft_unset.c \
	src/here_doc/heredoc.c \
	src/here_doc/heredoc_aux.c \

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

