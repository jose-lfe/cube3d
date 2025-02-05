/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 03:43:08 by jose-lfe          #+#    #+#             */
/*   Updated: 2025/02/05 15:15:06 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_print_error(char *str)
{
	ft_printf("Error\n");
	ft_printf("%s", str);
	exit(0);
}

void	ft_free_all(char *str, t_data *data)
{
	if (data->map != NULL)
		ft_free_str_map(data->map);
	if (data->map_int != NULL)
		free(data->map_int);
	if (data->no != NULL)
		free(data->no);
	if (data->so != NULL)
		free(data->so);
	if (data->we != NULL)
		free(data->we);
	if (data->ea != NULL)
		free(data->ea);
	if (str != NULL)
		ft_print_error(str);
	exit(0);
}

void	ft_error_get_info(char *str, char **map, t_data *data)
{
	ft_free_str_map(map);
	free(data->id);
	ft_free_all(str, data);
}

void	ft_free_all_game(t_game *game, char *str)
{
	if (game->no_tex.img)
		mlx_destroy_image(game->mlx, game->no_tex.img);
	if (game->so_tex.img)
		mlx_destroy_image(game->mlx, game->so_tex.img);
	if (game->we_tex.img)
		mlx_destroy_image(game->mlx, game->we_tex.img);
	if (game->ea_tex.img)
	{
		mlx_destroy_image(game->mlx, game->ea_tex.img);
	}
	ft_free_str_map(game->map);
	mlx_destroy_image(game->mlx, game->img);
	mlx_destroy_window(game->mlx, game->win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	if (str != NULL)
		ft_print_error(str);
	exit(0);
}
