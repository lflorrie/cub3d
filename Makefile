CC=gcc
CFLAGS =-Wall -Wextra
NAME= mlx-test
SRC = 	my_cub_utils.c \
		hero_parser.c \
		parser.c \
		#change_image_size.c
		#show_line.c
	
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