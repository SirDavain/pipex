NAME = pipex

SRC = pipex.c pipex_utils.c free_funcs.c

OBJ := $(SRC:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

libft:
	@make -C libft/

$(NAME): $(OBJ)
	@make -C libft/
	$(CC) $^ -Llibft -lft -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Ilibft -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	make fclean -C libft/

re: fclean all

.PHONY: NAME clean fclean re
