CC=gcc
CFLAGS =-Wall -Wextra -Werror
NAME= cub3D
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
DEP = $(SRC:.c=.d)

all:$(NAME)

-include $(OBJ:.o=.d)

%.o:%.c
	$(CC) -c $(CFLAGS) -Imlx -Ilibft  $< -o $@
	$(CC) -MM $(CFLAGS) -Imlx -Ilibft $< > $*.d

$(NAME):$(OBJ)
	$(MAKE) all -C mlx/
	cp mlx/libmlx.dylib .
	$(MAKE) bonus -C libft/
	$(CC) -o $(NAME) $(CFLAGS) $(OBJ) -Llibft/ -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

clean:
	rm -rf $(OBJ) $(DEP) && $(MAKE) clean -C libft/ && $(MAKE) clean -C mlx/

fclean: clean
	rm -rf $(NAME) && $(MAKE) fclean -C libft/ && rm -f mlx/libmlx.dylib

bonus:$(NAME)

re: fclean all

.PHONY: all clean fclean re