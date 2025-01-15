/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:41:01 by jose-lfe          #+#    #+#             */
/*   Updated: 2025/01/15 15:14:25 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kiki/cub3d.h"

int	ft_start_map(char *str)
{
	int i;

	i = 0;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	get_texture(char **str, t_data *data)
{
	int	flag;
	int	i;

	i = 0;
	flag = 0;
	while (str[i] && ft_start_map(str[i]) != 1)
	{
		
	}
	if (flag != 6)
	{
		ft_free_str_map(str);
		free_and_exit(data);
	}
	return (i);
}
