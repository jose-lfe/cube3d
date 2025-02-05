/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_texture.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 11:42:10 by kdroz             #+#    #+#             */
/*   Updated: 2025/02/05 14:54:09 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

t_texture	*resize_texture(t_game *g, t_texture *tex)
{
	t_texture	*n_tex;

	n_tex = malloc(sizeof(t_texture));
	if (!n_tex)
	{
		printf("Error: Failed to allocate memory for resized texture\n");
		free(tex->data);
		mlx_destroy_image(g->mlx, tex->img);
		exit(EXIT_FAILURE);
	}
	n_tex->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	n_tex->data = (int *)mlx_get_data_addr(n_tex->img, &g->bpp,
			&g->size_line, &g->endian);
	if (!n_tex->img || !n_tex->data)
	{
		printf("Error: Failed to create resized image\n");
		free(n_tex);
		free(tex->data);
		mlx_destroy_image(g->mlx, tex->img);
		exit(EXIT_FAILURE);
	}
	return (n_tex);
}

void	fill_texture_data(t_texture *texture, t_texture *resized_texture)
{
	int	x;
	int	y;
	int	tex_x;
	int	tex_y;
	int	color;

	y = 0;
	x = 0;
	while (y < HEIGHT)
	{
		while (x < WIDTH)
		{
			tex_x = x * texture->width / WIDTH;
			tex_y = y * texture->height / HEIGHT;
			color = texture->data[tex_y * texture->width + tex_x];
			resized_texture->data[y * WIDTH + x] = color;
			x++;
		}
		x = 0;
		y++;
	}
}

int	prepare_texture(t_game *g, t_texture *tex, char *f_path)
{
	int	*d;

	tex->img = mlx_xpm_file_to_image(g->mlx, f_path, &tex->width, &tex->height);
	free(f_path);
	if (!tex->img)
		return (-1);
	tex->data = (int *)malloc(tex->width * tex->height * sizeof(int));
	if (!tex->data)
		return (-1);
	d = (int *)mlx_get_data_addr(tex->img, &g->bpp, &g->size_line, &g->endian);
	if (!d)
	{
		free(tex->data);
		return (-1);
	}
	ft_memcpy(tex->data, d, tex->width * tex->height * sizeof(int));
	return (0);
}

void	load_texture(t_game *game, t_texture *texture, char *file_path)
{
	t_texture	*resized_texture;

	if (prepare_texture(game, texture, file_path) == -1)
		return ;
	resized_texture = resize_texture(game, texture);
	fill_texture_data(texture, resized_texture);
	mlx_destroy_image(game->mlx, texture->img);
	free(texture->data);
	texture->img = resized_texture->img;
	texture->data = resized_texture->data;
	texture->width = WIDTH;
	texture->height = HEIGHT;
	free(resized_texture);
}
