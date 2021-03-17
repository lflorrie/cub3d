INC=/usr/include

INCLIB=$(INC)/mlx_linux/lib

CC=gcc

CFLAGS= -I$(INC) -O3 -Imlx_linux/ -Wall

NAME= mlx-test
SRC = 	my_cub_utils.c \
		parser.c \
		#change_image_size.c
		#show_line.c 
	
OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME)	:$(OBJ)
	$(MAKE) bonus -C libft/
	$(CC) -o $(NAME) $(OBJ) -Llibft/ -lft -Lmlx_linux/ -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd

clean:
	rm -rf $(OBJ) && $(MAKE) clean -C libft/

fclean: clean
	rm -rf $(NAME) && $(MAKE) fclean -C libft/

re	: fclean all

.PHONY: all clean fclean re