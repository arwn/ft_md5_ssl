NAME=ft_ssl
CFLAGS=-Wall -Werror -Wextra -I. -Ilibft -g
LDFLAGS=-L libft/ -lft
OBJ=$(subst .c,.o,$(wildcard *.c))

$(NAME): $(OBJ)

lft:
	make -C libft

all: lft $(NAME)
	make -C libft

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	@norminette *.c *.h | grep -iv "warning"

norman: norm
	@norminette libft | grep -iv "warning"
