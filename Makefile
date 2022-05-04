NAME = minishell

SRC = $(wildcard src/*/*.c)\

INCLUDES = includes

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -I/Users/$(USER)/.brew/opt/readline/include

LIB = -lreadline -L/Users/$(USER)/.brew/opt/readline/lib

CC = gcc

$(RM) = rm -rf

.c.o: $(SRC) $(SRCB)
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c -o $@ $<
	@printf "%-42s\r" $@

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB)
	@printf "%-42s\r"

all: $(NAME)

clean:
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

run: $(NAME)
	@./$(NAME)

rerun: re run

.PHONY: $(NAME) all clean fclean re run rerun