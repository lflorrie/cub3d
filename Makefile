INC=/usr/include

INCLIB=$(INC)/mlx_linux/lib

CC=gcc

CFLAGS= -I$(INC) -O3 -Imlx_linux/ -Wall -Wextra -Werror

NAME= mlx-test
SRC = 	my_cub_utils.c \
		parser.c \
 		show_line.c \
		hero_parser.c \
		raycasting.c \
		proc_r.c \
		proc_fc.c \
		main.c \
		sprite.c \
		#change_image_size.c


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