NAME = cub3D
CC = gcc
CFLAGS = -Wall -Wextra -Werror
LIBFT_PATH = ./library/libft
MLX_PATH = ./library/minilibx-linux
LIBFT = -L$(LIBFT_PATH) -lft
MLX = -L$(MLX_PATH) -lmlx
FRAMEWORKS = -lmlx -lX11 -lXext -lm

SRCS = source/jojo/main.c source/jojo/error.c source/jojo/utils.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): libft_make $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(FRAMEWORKS) -lm -o $(NAME)

libft_make:
	make -C $(LIBFT_PATH) bonus

%.o: %.c
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -I$(MLX_PATH) -c $< -o $@

clean:
	rm -f $(OBJS)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all