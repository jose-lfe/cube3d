/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 14:15:51 by kdroz             #+#    #+#             */
/*   Updated: 2025/02/05 15:35:00 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "../libft/libft.h"
# include "../libft/get_next_line_bonus.h"
# include "../libft/ft_printf.h"

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
# define PI 3.14159265358979323846

typedef struct s_player
{
	float	x;
	float	y;
	float	new_x;
	float	new_y;
	float	angle;
	float	speed;
	float	angle_speed;
	bool	key_left;
	bool	key_right;
	bool	key_up;
	bool	key_down;
	bool	left_rotate;
	bool	right_rotate;

}	t_player;

typedef struct s_texture
{
	void	*img;
	int		*data;
	int		width;
	int		height;
	int		bpp;
	int		size_line;
	int		endian;
}	t_texture;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			size_line;
	int			endian;
	char		**map;
	t_player	player;
	t_texture	no_tex;
	t_texture	so_tex;
	t_texture	we_tex;
	t_texture	ea_tex;
	int			f_rgb;
	int			c_rgb;
}	t_game;

typedef struct s_ray {
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	side_dist_x;
	double	side_dist_y;
	int		map_x;
	int		map_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	wall_dist;
	double	wall_x;
}	t_ray;

typedef struct s_draw
{
	t_ray		ray;
	t_texture	*texture;
	double		perp_wall_dist;
	int			line_height;
	int			start_y;
	int			end_y;
	double		wall_x;
	int			tex_x;
}	t_draw;

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
void		ft_extract_rgb(char **map, char *id, char *info, t_data *data);

//jojo/main2.c
void		ft_print_map(char **str, t_data *data);
void		ft_get_map(int fd, char *test, t_data *data);
void		check_file_name(char *str);
//jojo/parsing.c
int			get_texture(char **str, t_data *data);
int			ft_start_map(char *str);

//jojo/error.c
void		ft_print_error(char *str);
void		ft_free_all(char *str, t_data *data);
void		ft_error_get_info(char *str, char **map, t_data *data);
void		ft_free_all_game(t_game *game, char *str);

//jojo/utils.c
t_data		init_data(void);
void		ft_free_str_map(char **map);
bool		ft_check_empty(char *str);
int			ft_compare(char *str, char *check);
char		*ft_get_id(char **map, char *str, int *i, t_data *data);

//jojo/converts.c
void		convert_map_int_to_char(t_data *data);
void		convert_map(char **str, int i, t_data *data);
void		convert_map2(char **str, int i, t_data *data);

//jojo/utils2.c
int			find_map_x(char **str, int i);
void		ft_get_player_data(char c, int y, int x, t_data *data);
int			ft_fill_map_int(char c);
int			ft_fill_map_char(t_data *data, int i, int x);
char		ft_fill_map_char2(int check);

//jojo/checks.c
void		check_for_player(int *map, int size, t_data *data);
void		check_bad_char(t_data *data);

void		check_map(t_data *d);
void		init_player(t_player *player, t_data *data);
int			key_press(int key, t_game *game);
int			key_release(int key, t_player *player);
void		move_player(t_game *game, t_player *player);
void		load_texture(t_game *game, t_texture *texture, char *file_path);
bool		touch(float px, float py, t_game *game);

int			draw_loop(t_game *game);
bool		touch(float px, float py, t_game *game);
void		init_ray(t_ray *ray, t_player *player, float angle);
void		ray_dir(t_ray *ray);
void		perform_dda(t_ray *ray, t_game *game);
t_texture	*select_texture(t_game *game, t_ray *ray);
double		calculate_wall_distance(t_ray *ray);
double		calculate_wall_coordinate(t_ray *ray, double perp_wall_dist);
int			calculate_texture_coordinate(t_game *game, t_ray *ray,
				t_texture *texture, double wall_x);
#endif