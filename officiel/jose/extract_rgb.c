/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 15:15:16 by kdroz             #+#    #+#             */
/*   Updated: 2025/02/05 15:15:25 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	extract_next_value(char **str)
{
	int	value;

	if (!str || !(*str) || !(**str))
		return (-1);
	value = ft_atoi(*str);
	while (**str && **str != ',')
	{
		(*str)++;
	}
	if (**str == ',')
	{
		(*str)++;
	}
	return (value);
}

void	error_extract_rgb(char **map, char *id, t_data *data)
{
	free(id);
	ft_free_str_map(map);
	ft_free_all("lack of RGB value\n", data);
}

void	ft_extract_rgb(char **map, char *id, char *info, t_data *data)
{
	int		r;
	int		g;
	int		b;
	char	*original_info;

	if (!info)
		error_extract_rgb(map, id, data);
	original_info = info;
	r = extract_next_value(&info);
	g = extract_next_value(&info);
	b = extract_next_value(&info);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free(original_info);
		free(id);
		ft_free_str_map(map);
		ft_free_all("incorect RGB value\n", data);
	}
	if (ft_compare(id, "c") == 1)
		data->c_rgb = (r << 16) | (g << 8) | b;
	if (ft_compare(id, "F") == 1)
		data->f_rgb = (r << 16) | (g << 8) | b;
	free(original_info);
}
