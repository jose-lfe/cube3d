/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:14:06 by kdroz             #+#    #+#             */
/*   Updated: 2025/02/05 15:14:06 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_for_player(int *map, int size, t_data *data)
{
	int	i;
	int	starting_point;

	i = 0;
	starting_point = 0;
	while (i < size)
	{
		if (map[i] != 0 && map[i] != 1 && map[i] != 6)
			starting_point ++;
		i++;
	}
	if (starting_point < 1)
		ft_free_all("No player inside the map\n", data);
	if (starting_point > 1)
		ft_free_all("Multiples players inside the map\n", data);
}

void	check_bad_char(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->map_s)
	{
		if (data->map_int[i] < 0)
		{
			ft_free_all("Invalid character inside the map\n", data);
		}
		i++;
	}
}
