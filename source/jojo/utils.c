/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 03:48:10 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/11/06 03:55:38 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_data	init_data(void)
{
	t_data	data;

	data.map_x = 0;
	data.map_y = 0;
	data.map_s = 0;
	data.map = NULL;
	data.mlx = NULL;
	data.win = NULL;
	data.NO_p = NULL;
	data.SO_p = NULL;
	data.WE_p = NULL;
	data.EA_p = NULL;
	data.NO_i = NULL;
	data.SO_i = NULL;
	data.WE_i = NULL;
	data.EA_i = NULL;
	data.F = 0;
	data.C = 0;
	return (data);
}
