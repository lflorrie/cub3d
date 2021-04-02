CC=gcc
CFLAGS =-Wall -Wextra
NAME= mlx-test
SRC = 	my_cub_utils.c \
		parser.c \
 		show_line.c \
		hero_parser.c \
		raycasting.c \
		proc_r.c \
		proc_fc.c \
		#change_image_size.c
	
OBJ = $(SRC:.c=.o)

%.o:%.c
	$(CC) -Imlx -Ilibft -c $< -o $@

all:$(NAME)


$(NAME):$(OBJ)
	$(MAKE) bonus -C libft/
	$(CC) -o $(NAME) $(OBJ) -Llibft/ -lft -Lmlx -lmlx -framework OpenGL -framework AppKit

clean:
	rm -rf $(OBJ) && $(MAKE) clean -C libft/

fclean: clean
	rm -rf $(NAME) && $(MAKE) fclean -C libft/

re: fclean all

.PHONY: all clean fclean re