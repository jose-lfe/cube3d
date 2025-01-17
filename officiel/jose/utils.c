/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 03:48:10 by jose-lfe          #+#    #+#             */
/*   Updated: 2025/01/17 16:03:55 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kiki/cub3d.h"

t_data	init_data(void)
{
	t_data	data;

	data.map_x = 0;
	data.map_y = 0;
	data.map_s = 0;
	data.map = NULL;
	data.no = NULL;
	data.so = NULL;
	data.we = NULL;
	data.ea = NULL;
	data.f_rgb = 0;
	data.c_rgb = 0;
	return (data);
}

void	ft_free_str_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

bool	ft_check_empty(char *str)
{
	while (*str)
	{
		if (*str != ' ' && *str != '\t' && *str != '\n'
			&& *str != '\v' && *str != '\f' && *str != '\r')
		{
			return (false);
		}
		str++;
	}
	return (true);
}

int	ft_compare(char *str, char *check)
{
	if (ft_strlen(str) == ft_strlen(check))
	{
		if (ft_strncmp(str, check, ft_strlen(str)) == 0)
			return (1);
	}
	return (0);
}

char	*ft_get_id(char *str, int *i)
{
	int		y;
	char	*id;

	y = 0;
	while (str[*i + y] && str[*i + y] != ' ')
		y++;
	id = malloc((y + 1) * sizeof(char));
	if (!id)
		ft_print_error("malloc error");
	y = 0;
	while (str[*i] && str[*i] != ' ')
	{
		id[y] = str[*i];
		(*i)++;
		y++;
	}
	id[y] = '\0';
	return (id);
}
