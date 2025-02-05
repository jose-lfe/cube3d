/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   converts.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:14:57 by kdroz             #+#    #+#             */
/*   Updated: 2025/02/05 15:14:57 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	convert_map_int_to_char(t_data *data)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	data->map = malloc((data->map_y + 1) * sizeof(char *));
	if (data->map == NULL)
		ft_free_all("Malloc Error\n", data);
	while (i < data->map_y)
	{
		x = ft_fill_map_char(data, i, x);
		if (x == 0)
		{
			ft_free_all("invalid map\n", data);
		}
		i++;
	}
	data->map[i] = NULL;
	free(data->map_int);
	data->map_int = NULL;
}

void	convert_map2(char **str, int i, t_data *data)
{
	data->map_x = find_map_x(str, i);
	data->map_s = data->map_x * data->map_y;
	data->map_int = malloc(data->map_s * sizeof(int));
}

void	convert_map(char **str, int i, t_data *data)
{
	int		y;
	int		tmp;
	int		d;
	int		len;

	y = 1;
	d = 0;
	while (str[i + y])
		y ++;
	data->map_y = y;
	convert_map2(str, i, data);
	while (str[i])
	{
		tmp = 0;
		len = ft_strlen(str[i]);
		while (tmp < data->map_x)
		{
			if (tmp < len)
				data->map_int[d++] = ft_fill_map_int(str[i][tmp]);
			else
				data->map_int[d++] = 1;
			tmp++;
		}
		i++;
	}
}
