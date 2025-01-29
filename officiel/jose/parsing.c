/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:41:01 by jose-lfe          #+#    #+#             */
/*   Updated: 2025/01/28 16:27:04 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kiki/cub3d.h"

int	ft_start_map(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != ' ' && str[i] != 'E'
			&& str[i] != 'N' && str[i] != 'S' && str[i] != 'W')
			return (0);
		i++;
	}
	return (1);
}

char	*ft_get_info(char **map, char *str, int i, t_data *data)
{
	int		y;
	char	*info;

	while (str[i] && str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (NULL);
	y = 0;
	while (str[i + y] && str[i + y] != ' ')
		y++;
	info = malloc((y + 1) * sizeof(char));
	if (!info)
		ft_error_get_info("Malloc error\n", map, data);
	y = 0;
	while (str[i] && str[i] != ' ')
		info[y++] = str[i++];
	info[y] = '\0';
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
		ft_error_get_info("Format not respected\n", map, data);
	return (info);
}

void	ft_put_info(char **map, char *id, char *info, t_data *data)
{
	if (info == NULL)
	{
		printf("Error\n");
		printf("No path for texture :%s\n", id);
		free(id);
		ft_free_str_map(map);
		ft_free_all(NULL, data);
	}
	if (ft_compare(id, "NO") == 1)
		data->no = info;
	if (ft_compare(id, "SO") == 1)
		data->so = info;
	if (ft_compare(id, "WE") == 1)
		data->we = info;
	if (ft_compare(id, "EA") == 1)
		data->ea = info;
	printf("%s : %s\n", id, info); //
}

void	ft_get_texture2(char **map, char *str, t_data *data)
{
	int		i;
	char	*info;

	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	data->id = ft_get_id(map, str, &i, data);
	printf("id: %s\n", data->id); // effacer plus tard
	info = ft_get_info(map, str, i, data);
	if (ft_compare(data->id, "NO") == 1 || ft_compare(data->id, "SO") == 1
		|| ft_compare(data->id, "WE") == 1 || ft_compare(data->id, "EA") == 1)
		ft_put_info(map, data->id, info, data);
	else if (ft_compare(data->id, "C") == 1 || ft_compare(data->id, "F") == 1)
		ft_extract_rgb(map, data->id, info, data);
	else
	{
		if (info != NULL)
			free(info);
		free(data->id);
		ft_free_str_map(map);
		printf("Error\n%s: is not a correct identifier", data->id);
		ft_free_all(NULL, data);
	}
	free(data->id);
}

int	get_texture(char **str, t_data *data)
{
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	while (str[i] && ft_start_map(str[i]) != 1)
	{
		if (ft_check_empty(str[i]) == false)
		{
			ft_get_texture2(str, str[i], data);
			flag++;
		}
		i++;
	}
	if (flag < 6)
	{
		ft_free_str_map(str);
		ft_free_all("Not enought elements about the map\n", data);
	}
	if (flag > 6)
	{
		ft_free_str_map(str);
		ft_free_all("too many elements about the map\n", data);
	}
	return (i);
}
