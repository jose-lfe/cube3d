/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:11:27 by kdroz             #+#    #+#             */
/*   Updated: 2025/01/31 12:57:59 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	calculate_wall_distance(t_ray *ray)
{
	if (ray->side == 0)
		return ((ray->map_x - ray->pos_x + (1 - ray->step_x) / 2) / ray->dir_x);
	else
		return ((ray->map_y - ray->pos_y + (1 - ray->step_y) / 2) / ray->dir_y);
}

double	calculate_wall_coordinate(t_ray *ray, double perp_wall_dist)
{
	if (ray->side == 0)
		return (ray->pos_y + perp_wall_dist * ray->dir_y);
	else
		return (ray->pos_x + perp_wall_dist * ray->dir_x);
}

int	calculate_texture_coordinate(t_game *g, t_ray *ray,
		t_texture *tex, double wall_x)
{
	int	tex_x;

	tex_x = (int)(wall_x * tex->width);
	if (((ray->side == 0 && ray->dir_x < 0)
			|| (ray->side == 1 && ray->dir_y < 0))
		&& tex != &g->no_tex)
	{
		tex_x = tex->width - tex_x - 1;
		tex_x = tex_x % tex->width;
	}
	return (tex_x);
}
