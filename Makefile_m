CC=gcc
CFLAGS =-Wall -Wextra -Werror
NAME= mlx-test
SRC = hero_parser.c \
		init_mlx_func.c \
		main.c \
		map_utils.c \
		my_cub_utils.c \
		parser.c \
		proc_fc.c \
		proc_keys.c \
		proc_r.c \
		proc_wasd.c \
		raycast_utils.c \
		raycasting.c \
 		show_line.c \
		sprite.c \
		sprite_utils.c \
		sprite_array.c \
		make_bmp_screen_shot.c \
		validate_map.c
	
OBJ = $(SRC:.c=.o)

%.o:%.c
	$(CC) -Imlx -Ilibft -c $< -o $@

all:$(NAME)


$(NAME):$(OBJ)
	$(MAKE) bonus -C libft/
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) -Llibft/ -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

clean:
	rm -rf $(OBJ) && $(MAKE) clean -C libft/

fclean: clean
	rm -rf $(NAME) && $(MAKE) fclean -C libft/

re: fclean all

.PHONY: all clean fclean re