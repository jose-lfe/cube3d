/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 03:43:08 by jose-lfe          #+#    #+#             */
/*   Updated: 2025/01/28 16:27:10 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kiki/cub3d.h"

void	ft_print_error(char *str)
{
	ft_printf("Error\n");
	ft_printf("%s\n", str);
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
