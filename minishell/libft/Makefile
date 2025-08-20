# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alejogogi <alejogogi@student.42.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/18 10:06:50 by alejogogi         #+#    #+#              #
#    Updated: 2024/10/24 17:22:39 by alejogogi        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC =	ft_split.c ft_strtrim.c ft_strmapi.c ft_strjoin.c ft_atoi.c\
		ft_bzero.c ft_substr.c ft_calloc.c ft_isalnum.c ft_isalpha.c\
		ft_isascii.c ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c\
		ft_memcmp.c ft_memcpy.c ft_memmove.c ft_memset.c ft_putchar_fd.c\
 		ft_putendl_fd.c ft_putnbr_fd.c ft_putstr_fd.c ft_strchr.c ft_strdup.c\
  		ft_striteri.c ft_strlcat.c ft_strlcpy.c ft_strlen.c ft_strncmp.c\
   		ft_strnstr.c ft_strrchr.c ft_tolower.c ft_toupper.c ft_strcmp.c\

OBJ = $(SRC:.c=.o)

INCLUDE = libft.h

AR = ar rcs
RM = rm -f

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(AR) $(NAME) $(OBJ)
 
%.o: %.c $(INCLUDE)
	$(CC) $(CFLAGS) -c -o $@ $<
	
clean: 
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all