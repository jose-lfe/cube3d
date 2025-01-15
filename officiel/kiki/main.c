#include "cub3d.h"


void put_pixel(int x, int y, int color, t_game *game)
{
	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	if (color < 0 || color > 0xFFFFFF)
	{
    	fprintf(stderr, "Error: Invalid color value: %d\n", color);
	}
	int index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	draw_square(int x, int y, int size, int color, t_game *game)
{
	int i;

	i = 0;
	while (i++ < size)
		put_pixel(x + i, y, color, game);
	i = 0;
	while (i++ < size)
		put_pixel(x, y + i, color, game);
	i = 0;
	while (i++ < size)
		put_pixel(x + size, y + i, color, game);
	i = 0;
	while (i++ < size)
		put_pixel(x + i, y + size, color, game);
}

void	draw_map(t_game *game)
{
	char **map;
	int color;
	int x;
	int y;
	
	map = game->map;
	color = 0x0000FF;
	x = 0;
	y = 0;
	while (map[y] != NULL)
	{
		x = 0;
		while (map[y][x] != 0)
		{
			if (map[y][x] == '1')
				draw_square(x * BLOCK, y * BLOCK, BLOCK, color, game);
			x++;
		}
		y++;
	}
	
}

char **get_map(void)
{
	char **map = malloc(sizeof(char *) * 11);
	map[0] = "111111111111111";
	map[1] = "100000000000001";
	map[2] = "100000000000001";
	map[3] = "100000000000001";
	map[4] = "100000000000001";
	map[5] = "100100000000001";
	map[6] = "100000000000001";
	map[7] = "100001000100001";
	map[8] = "101100000110001";
	map[9] = "111111111111111";
	map[10] = NULL;
	return (map);
}

void	clear_image(t_game *game)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(x, y, 0, game);
			x++;
		}
		y++;
	}
}

void init_game(t_game *game)
{
	init_player(&game->player);
	game->map = get_map();
	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, WIDTH, HEIGHT, "Game");
	game->img = mlx_new_image(game->mlx, WIDTH, HEIGHT);
	game->data = mlx_get_data_addr(game->img, &game->bpp, &game->size_line, &game->endian);
	load_texture(game, &game->wall_texture, "./kiki/textures/wall_texture.xpm");
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);

}

bool	touch(float px, float py, t_game *game)
{
	int x = px / BLOCK;
	int y = py / BLOCK;
	if (game->map[y][x] == '1')
		return true;
	else
		return false;
}

float distance(float x, float y)
{
	return sqrt(x * x + y * y);
}

float fixed_dist(float x1, float y1, float x2, float y2, t_game *game)
{
	float delta_x = x2 - x1;
	float delta_y = y2 - y1;
	float angle = atan2(delta_y, delta_x) - game->player.angle;
	float fix_dist = distance(delta_x, delta_y) * cos(angle);
	return (fix_dist);
}

void draw_wall_line(t_game *game, int x, int start_y, int end_y, t_texture *texture, int tex_x) {
    int wall_height = end_y - start_y;
    for (int y = start_y; y < end_y; y++) {
        float tex_y_ratio = (y - start_y) / (float)wall_height; // Ratio of the wall height
        int tex_y = (int)(tex_y_ratio * texture->height); // Calculate the texture Y coordinate

        // Ensure tex_x and tex_y are within bounds
        if (tex_x < 0 || tex_x >= texture->width || tex_y < 0 || tex_y >= texture->height) {
            continue; // Skip this iteration if out of bounds
        }

        // Get the color from the texture
        int color = texture->data[tex_y * texture->width + tex_x];
        put_pixel(x, y, color, game);
    }
}


void	draw_line(t_player *player, t_game *game, float start_x, int i)
{
	float cos_angle = cos(start_x);
	float sin_angle = sin(start_x);
	float ray_x = player->x;
	float ray_y = player->y;
	bool is_vertical = false;

	while (!touch(ray_x, ray_y, game))
	{
		if (DEBUG == 1)
			put_pixel(ray_x, ray_y, 0xFF0000, game);
		if (fmod(ray_x, BLOCK == 0))
			is_vertical = true;
		else
			is_vertical = false;
		ray_x += cos_angle;
		ray_y += sin_angle;
	}

	float dist = fixed_dist(player->x, player->y, ray_x, ray_y, game);
	float height = (BLOCK / dist) * (WIDTH / 2);
	int start_y = (HEIGHT - height) / 2;
	int end_y = start_y + height;
	while (start_y < end_y)
	{
		if (DEBUG == 0)
			put_pixel(i, start_y, 255, game);
		start_y++;
	}
	start_y = (HEIGHT - height) / 2;
	if (is_vertical)
	{
		int tex_x = (int)(fmod(ray_y, BLOCK) / BLOCK * game->wall_texture.width);
		draw_wall_line(game, i, start_y, end_y, &game->wall_texture, tex_x);
	}
	else
	{
		int tex_x = (int)(fmod(ray_x, BLOCK) / BLOCK * game->wall_texture.width);
		draw_wall_line(game, i, start_y, end_y, &game->wall_texture, tex_x);
	}
}

int draw_loop(t_game *game)
{
	t_player *player = &game->player;
	move_player(player);
	clear_image(game);
	if (DEBUG == 1)
	{
		draw_square(player->x, player->y, 10, 0x00FF00, game);
		draw_map(game);
	}

	float fraction = PI / 3 / WIDTH;
	float start_x = player->angle - PI / 6;
	int i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}

	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return 0;
}

int main(void)
{
	t_game game;

	init_game(&game);

	mlx_hook(game.win, 2, 1L<<0, key_press, &game.player);
	mlx_hook(game.win, 3, 1L<<1, key_release, &game.player);
	//mlx_hook(game.win, EVENT_CLOSE_BTN, 0, mlx_loop_end, game.mlx);

	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);

	return (0);
}