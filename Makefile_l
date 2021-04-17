INC=/usr/include

INCLIB=$(INC)/mlx_linux/lib

CC=gcc

CFLAGS= -I$(INC) -O3 -Imlx_linux/ -Wall -Wextra -Werror

NAME= mlx-test
SRC = 	hero_parser.c \
		main.c \
		map_utils.c \
		my_cub_utils.c \
		parser.c \
		proc_fc.c \
		proc_keys.c \
		proc_r.c \
		proc_wasd.c \
		raycasting.c \
 		show_line.c \
		sprite.c \
		validate_map.c


OBJ = $(SRC:.c=.o)

%.o:%.c
	$(CC) -Imlx_linux -Ilibft -c $< -o $@
	

all:$(NAME)

$(NAME)	:$(OBJ)
	$(MAKE) bonus -C libft/
	$(CC) -o $(NAME) $(OBJ) -Llibft/ -lft -Lmlx_linux/ -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd -Wall -Wextra -Werror

clean:
	rm -rf $(OBJ) && $(MAKE) clean -C libft/

fclean: clean
	rm -rf $(NAME) && $(MAKE) fclean -C libft/

re	: fclean all

.PHONY: all clean fclean re