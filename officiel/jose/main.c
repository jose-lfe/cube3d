/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:19:54 by kdroz             #+#    #+#             */
/*   Updated: 2025/02/05 15:13:00 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *g, t_data *data)
{
	init_player(&g->player, data);
	g->map = data->map;
	g->mlx = mlx_init();
	g->win = mlx_new_window(g->mlx, WIDTH, HEIGHT, "Game");
	g->img = mlx_new_image(g->mlx, WIDTH, HEIGHT);
	g->data = mlx_get_data_addr(g->img, &g->bpp, &g->size_line, &g->endian);
	g->no_tex.img = NULL;
	g->so_tex.img = NULL;
	g->ea_tex.img = NULL;
	g->we_tex.img = NULL;
	load_texture(g, &g->no_tex, data->no);
	load_texture(g, &g->so_tex, data->so);
	load_texture(g, &g->we_tex, data->we);
	load_texture(g, &g->ea_tex, data->ea);
	if (g->no_tex.img == NULL)
		ft_free_all_game(g, "failed to load north texture\n");
	if (g->so_tex.img == NULL)
		ft_free_all_game(g, "failed to load south texture\n");
	if (g->we_tex.img == NULL)
		ft_free_all_game(g, "failed to load west texture\n");
	if (g->ea_tex.img == NULL)
		ft_free_all_game(g, "failed to load east texture\n");
	g->f_rgb = data->f_rgb;
	g->c_rgb = data->c_rgb;
	mlx_put_image_to_window(g->mlx, g->win, g->img, 0, 0);
}

void	init_player(t_player *player, t_data *data)
{
	player->x = data->player_x * BLOCK + BLOCK / 2;
	player->y = data->player_y * BLOCK + BLOCK / 2;
	player->new_x = player->x;
	player->new_y = player->y;
	player->angle = data->player_angle;
	player->speed = 4.0;
	player->angle_speed = 0.015;
	player->key_left = false;
	player->key_right = false;
	player->key_up = false;
	player->key_down = false;
	player->left_rotate = false;
	player->right_rotate = false;
}

int	close_win(void *param)
{
	t_game	*game;

	game = (t_game *)param;
	ft_free_all_game(game, NULL);
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	char	*tmp;
	t_game	game;
	t_data	data;

	fd = 0;
	data = init_data();
	if (ac != 2)
		ft_print_error("Single argument required (*.cub)");
	check_file_name(av[1]);
	fd = open(av[1], fd, O_RDONLY);
	if (fd == -1)
		ft_print_error("Error opening file");
	tmp = get_next_line(fd);
	if (!tmp)
		ft_print_error("empty map");
	ft_get_map(fd, tmp, &data);
	init_game(&game, &data);
	mlx_hook(game.win, 2, 1L << 0, key_press, &game);
	mlx_hook(game.win, 3, 1L << 1, key_release, &game.player);
	mlx_hook(game.win, 17, 0, close_win, &game);
	mlx_loop_hook(game.mlx, draw_loop, &game);
	mlx_loop(game.mlx);
	return (0);
}
