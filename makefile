NAME=ft_ssl
CFLAGS=-Wall -Werror -Wextra -I. -Ilibft
OBJ=$(subst .c,.o,$(wildcard *.c))

$(NAME): $(OBJ)

all: $(NAME)
	make -C libft

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all
