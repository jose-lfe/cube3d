# Compiler
CC = gcc

# Executable name
NAME = cub3d

# Directories
SRC_DIR = jose
OBJ_DIR = obj
LIBFT_PATH = ./libft
MLX_PATH = ./mlx
LIBFT = -L$(LIBFT_PATH) -lft
LIBMLX = -L$(MLX_PATH) -lft

# Sources
SRC = 	$(SRC_DIR)/main2.c \
		$(SRC_DIR)/error.c \
		$(SRC_DIR)/extract_rgb.c \
		$(SRC_DIR)/parsing.c \
		$(SRC_DIR)/draw.c \
		$(SRC_DIR)/raycasting.c \
		$(SRC_DIR)/raycasting2.c \
		$(SRC_DIR)/utils.c \
		$(SRC_DIR)/utils2.c \
		$(SRC_DIR)/checks.c \
		$(SRC_DIR)load_texture.c \
		$(SRC_DIR)player.c \
		$(SRC_DIR)main.c \
		$(SRC_DIR)check_map.c \
		$(SRC_DIR)/converts.c
OBJ =	$(OBJ_DIR)/main2.o \
		$(OBJ_DIR)/error.o \
		$(OBJ_DIR)/extract_rgb.o \
		$(OBJ_DIR)/parsing.o \
		$(OBJ_DIR)/draw.o \
		$(OBJ_DIR)/raycasting.o \
		$(OBJ_DIR)/raycasting2.o \
		$(OBJ_DIR)/utils.o \
		$(OBJ_DIR)/utils2.o \
		$(OBJ_DIR)/checks.o \
		$(OBJ_DIR)/load_texture.o \
		$(OBJ_DIR)/player.o \
		$(OBJ_DIR)/main.o \
		$(OBJ_DIR)/check_map.o \
		$(OBJ_DIR)/converts.o

# SRC = 	$(SRC_DIR)/main.c \
# 		$(SRC_DIR)/player.c \
# 		$(SRC_DIR)/texture.c
# OBJ =	$(OBJ_DIR)/main.o \
# 		$(OBJ_DIR)/player.o \
# 		$(OBJ_DIR)/texture.o

# Compiler flags
CFLAGS = -Wall -Wextra -Werror -g

# Linker flags
LDFLAGS = -lmlx -lX11 -lXext -lm

# Targets
all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_PATH)/libft.a $(MLX_PATH)/libmlx.a
	$(CC) $(OBJ) $(LDFLAGS) $(LIBFT) $(LIBMLX) -o $(NAME)

# Object files compilation
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(LIBFT_PATH) -I$(MLX_PATH) -c $< -o $@

# Create object directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(LIBFT_PATH)/libft.a:  # Règle pour ne compiler libft que si nécessaire
	make -C $(LIBFT_PATH) bonus

$(MLX_PATH)/libmlx.a:  # Règle pour ne compiler mlx que si nécessaire
	make -C $(MLX_PATH)

# Clean
clean:
	rm -rf $(OBJ_DIR)
	make -C $(LIBFT_PATH) clean
	make -C $(MLX_PATH) clean

fclean: clean
	rm -f $(NAME)
	make -C $(LIBFT_PATH) fclean
	make -C $(MLX_PATH) clean


re: fclean all

.PHONY: all clean fclean re
