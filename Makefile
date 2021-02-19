INC=/usr/include
HT=Linux
DOCP=do_cp



INCLIB=$(INC)/mlx_linux/lib

CC=gcc

CFLAGS= -I$(INC) -O3 -Imlx_linux/

NAME= mlx-test
SRC = hello.c
OBJ = $(SRC:.c=.o)

all:$(NAME)

$(NAME)	:$(OBJ)
	$(CC) -o $(NAME) $(OBJ) -Lmlx_linux/ -lmlx -L$(INCLIB) -lXext -lX11 -lm -lbsd

clean:
	rm -f $(NAME) $(OBJ) *~ core *.core


re	: clean all
