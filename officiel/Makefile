# Compiler
CC = gcc

# Executable name
NAME = cub3d

# Directories
SRC_DIR = kiki
OBJ_DIR = obj
MLX_DIR = mlx
LIBFT_PATH = ./libft
LIBFT = -L$(LIBFT_PATH) -lft

# Sources
SRC = 	$(SRC_DIR)/main.c \
		$(SRC_DIR)/player.c \
		$(SRC_DIR)/texture.c
OBJ =	$(OBJ_DIR)/main.o \
		$(OBJ_DIR)/player.o \
		$(OBJ_DIR)/texture.o

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -I$(MLX_DIR)

# Linker flags
LDFLAGS = -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

# Targets
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_PATH)/libft.a
	$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

# Object files compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -c $< -o $@

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_PATH)/libft.a:  # Règle pour ne compiler libft que si nécessaire
	make -C $(LIBFT_PATH) bonus

# Clean
clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) clean

re: fclean all

.PHONY: all clean fclean re
