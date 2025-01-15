#ifndef CUB3D_H
#define CUB3D_H

#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
# include "libft.h"
# include "get_next_line_bonus.h"
# include "ft_printf.h"

# define DEBUG 1
# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 64
# define EVENT_CLOSE_BTN 17
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100
# define KEY_ESC 65307
# define KEY_Q 113
# define KEY_E 101
# define PI 3.141592653589

typedef struct s_player
{
	float	x;
	float	y;
	float	angle;

	bool	key_left;
	bool	key_right;
	bool	key_up;
	bool	key_down;
	bool	left_rotate;
	bool	right_rotate;

} t_player;

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
} t_texture;

typedef struct s_game
{
	void	*mlx;
	void	*win;
	void	*img;

	char	*data;
	int		bpp;
	int		size_line;
	int		endian;

	char**	map;

	t_player	player;
	t_texture	wall_texture;

} t_game;

typedef struct s_map
{
}	t_map;

typedef struct s_data
{
	int		map_x;
	int		map_y;
	int		map_s;
	int		*map;
	void	*mlx;
	void	*win;
	void	*NO_p;
	void	*SO_p;
	void	*WE_p;
	void	*EA_p;
	int		*NO_i;
	int		*SO_i;
	int		*WE_i;
	int		*EA_i;
	int		F;
	int		C;
}	t_data;

//jojo/parsing.c
int		get_texture(char **str, t_data *data);

//jojo/error.c
void	ft_print_error(char *str);

//jojo/utils.c
t_data	init_data(void);
void	ft_free_str_map(char **map);


void	init_player(t_player *player);
int		key_press(int key, t_player *player);
int		key_release(int key, t_player *player);
void	move_player(t_player *player);
void	load_texture(t_game *game, t_texture *texture, char *file_path);

#endif