#ifndef CUB3D_H
#define CUB3D_H

#include "../mlx/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
# include "../libft/libft.h"
# include "../libft/get_next_line_bonus.h"
# include "../libft/ft_printf.h"

# define DEBUG 1
# define WIDTH 1280
# define HEIGHT 720
# define BLOCK 256
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

typedef struct s_data
{
	int		map_x;
	int		map_y;
	int		map_s;
	char	**map;
	int		*map_int;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*id;
	int		f_rgb;
	int		c_rgb;
	float	player_x;
	float	player_y;
	float	player_angle;
}	t_data;

//jojo/extract_rgb
void	ft_extract_rgb(char **map, char *id, char *info, t_data *data);

//jojo/parsing.c
int		get_texture(char **str, t_data *data);

//jojo/error.c
void	ft_print_error(char *str);
void	ft_free_all(char *str, t_data *data);
void	ft_error_get_info(char *str, char **map, t_data *data);

//jojo/utils.c
t_data	init_data(void);
void	ft_free_str_map(char **map);
bool	ft_check_empty(char *str);
int		ft_compare(char *str, char *check);
char	*ft_get_id(char **map, char *str, int *i, t_data *data);

//jojo/converts.c
void	convert_map_int_to_char(t_data *data);
void	convert_map(char **str, int	i, t_data *data);
void	convert_map2(char **str, int i, t_data *data);

//jojo/utils2.c
int		find_map_x(char **str, int i);
void	ft_get_player_data(char c, int y, int x, t_data *data);
int		ft_fill_map_int(char c);
int		ft_fill_map_char(t_data *data, int i, int x);
char	ft_fill_map_char2(int	check);

//jojo/checks.c
void	check_for_player(int *map, int size, t_data *data);
void	check_bad_char(t_data *data);

void	init_player(t_player *player);
int		key_press(int key, t_player *player);
int		key_release(int key, t_player *player);
void	move_player(t_player *player);
void	load_texture(t_game *game, t_texture *texture, char *file_path);

#endif