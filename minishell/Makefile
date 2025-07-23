NAME = minishell
CC = cc
CFLAGS = -Wall -Werror -Wextra
SRC = main.c prompt.c lexer.c lexer_quotes.c
OBJ = $(SRC:.c=.o)
RM = rm -f

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME) -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all
