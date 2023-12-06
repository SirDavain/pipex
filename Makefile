NAME = pipex

SRC = main.c

OBJ := $(SRC:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

libft:
	@make -C libft/

$(NAME): $(OBJ)
	@make -c libft/
	$(CC) $^ -Llibft -lft -o $(NAME)

%.o: %.C
	$(CC) $(CFLAGS) -Ilibft -c $< -o $@

clean
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: NAME clean fclean re
