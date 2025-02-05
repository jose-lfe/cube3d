/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:34:43 by kdroz             #+#    #+#             */
/*   Updated: 2025/02/05 14:52:08 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	check_y(t_data *d, int x, int y, int i)
{
	bool	flag;

	flag = false;
	while (y < d->map_x && y > 0)
	{
		y = y + i;
		if (d->map[x][y] == '1')
		{
			flag = true;
			break ;
		}
		if (d->map[x][y] == ' ')
			break ;
		flag = false;
	}
	return (flag);
}

bool	check_x(t_data *d, int x, int y, int i)
{
	bool	flag;

	flag = false;
	while (x < d->map_y - 1 && x > 0)
	{
		x = x + i;
		if (d->map[x][y] == '1')
		{
			flag = true;
			break ;
		}
		if (d->map[x][y] == ' ')
			break ;
		flag = false;
	}
	return (flag);
}

bool	check_map2(t_data *d, int x, int y)
{
	if (x == d->map_y - 1 || x == 0)
		return (false);
	if (y == d->map_x || y == 0)
		return (false);
	if (check_x(d, x, y, 1) == false)
		return (false);
	if (check_x(d, x, y, -1) == false)
		return (false);
	if (check_y(d, x, y, 1) == false)
		return (false);
	if (check_y(d, x, y, -1) == false)
		return (false);
	return (true);
}

void	check_map(t_data *d)
{
	int	y;
	int	x;

	y = 0;
	x = 0;
	while (x <= d->map_y - 1)
	{
		while (y <= d->map_x)
		{
			if (d->map[x][y] == '0')
			{
				if (check_map2(d, x, y) == false)
					ft_free_all("Map is not closed\n", d);
			}
			y++;
		}
		x++;
		y = 0;
	}
	return ;
}
