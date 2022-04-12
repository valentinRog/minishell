 NAME = minishell

SRC = $(wildcard src/main/*.c)\
      $(wildcard src/parsing/*.c)\
      $(wildcard src/utils/*.c)

INCLUDES = includes

OBJ = $(SRC:.c=.o)

CFLAGS = -fsanitize=address

LIB = -lreadline

CC = gcc

$(RM) = rm -rf

.c.o: $(SRC) $(SRCB)
	@printf "%-33.33s\r" $@
	@$(CC) $(CFLAGS) -I $(INCLUDES) -c -o $@ $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LIB)

all: $(NAME)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

run: $(NAME)
	./$(NAME)

rerun: re run

.PHONY: $(NAME) all clean fclean re run