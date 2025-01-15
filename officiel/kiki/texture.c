#include "cub3d.h"

void	load_texture(t_game *game, t_texture *texture, char *file_path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, file_path, &texture->width, &texture->height);
	if (!texture->img)
	{
		fprintf(stderr, "Error, Failed to load texture from %s\n", file_path);
		exit(EXIT_FAILURE);
	}
	texture->data = (int *)mlx_get_data_addr(texture->img, &game->bpp, &game->size_line, &game->endian);
	if (!texture->data)
	{
    fprintf(stderr, "Error: Failed to get data address for texture\n");
    exit(EXIT_FAILURE);
	}
	if (texture->width <= 0 || texture->height <= 0)
	{
    fprintf(stderr, "Error: Invalid texture dimensions: %dx%d\n", texture->width, texture->height);
    exit(EXIT_FAILURE);
	}
}
