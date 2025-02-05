/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:05:46 by kdroz             #+#    #+#             */
/*   Updated: 2025/02/05 14:12:58 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(int x, int y, int color, t_game *game)
{
	int	index;

	if (x >= WIDTH || y >= HEIGHT || x < 0 || y < 0)
		return ;
	if (color < 0 || color > 0xFFFFFF)
	{
		fprintf(stderr, "Error: Invalid color value: %d\n", color);
	}
	index = y * game->size_line + x * game->bpp / 8;
	game->data[index] = color & 0xFF;
	game->data[index + 1] = (color >> 8) & 0xFF;
	game->data[index + 2] = (color >> 16) & 0xFF;
}

void	clear_image(t_game *game)
{
	int	x;
	int	y;
	int	ceiling_color;
	int	floor_color;

	ceiling_color = game->c_rgb;
	floor_color = game->f_rgb;
	x = 0;
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < HEIGHT / 2)
				put_pixel(x, y, ceiling_color, game);
			else
				put_pixel(x, y, floor_color, game);
			x++;
		}
		y++;
	}
}

void	draw_wall_line(t_game *game, int x, t_draw *d)
{
	int		line_height;
	int		y;
	double	tex_pos;
	int		tex_y;
	int		color;

	line_height = d->end_y - d->start_y;
	y = d->start_y;
	while (y < d->end_y)
	{
		if (y < 0 || y >= HEIGHT)
		{
			y++;
			continue ;
		}
		tex_pos = (y - d->start_y) * d->texture->height / line_height;
		tex_y = (int)tex_pos % (d->texture->height);
		color = d->texture->data[tex_y * d->texture->width + d->tex_x];
		put_pixel(x, y, color, game);
		y++;
	}
}

void	draw_line(t_player *player, t_game *game, float angle, int x)
{
	t_draw	d;

	init_ray(&d.ray, player, angle);
	perform_dda(&d.ray, game);
	d.perp_wall_dist = calculate_wall_distance(&d.ray);
	d.line_height = (int)(HEIGHT / (d.perp_wall_dist
				* cos(angle - player->angle)));
	d.start_y = -d.line_height / 2 + HEIGHT / 2;
	d.end_y = d.line_height / 2 + HEIGHT / 2;
	d.texture = select_texture(game, &d.ray);
	d.wall_x = calculate_wall_coordinate(&d.ray, d.perp_wall_dist);
	d.wall_x -= floor(d.wall_x);
	d.tex_x = calculate_texture_coordinate(game, &d.ray, d.texture, d.wall_x);
	draw_wall_line(game, x, &d);
}

int	draw_loop(t_game *game)
{
	float		fraction;
	float		start_x;
	int			i;
	t_player	*player;

	player = &game->player;
	move_player(game, player);
	clear_image(game);
	fraction = PI / 3 / WIDTH;
	start_x = ((player->angle - PI / 6));
	i = 0;
	while (i < WIDTH)
	{
		draw_line(player, game, start_x, i);
		start_x += fraction;
		i++;
	}
	mlx_put_image_to_window(game->mlx, game->win, game->img, 0, 0);
	return (0);
}
