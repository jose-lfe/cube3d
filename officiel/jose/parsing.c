/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 11:41:01 by jose-lfe          #+#    #+#             */
/*   Updated: 2025/01/20 13:50:50 by jose-lfe         ###   ########.fr       */
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

char	*ft_get_info(char *str, int i)
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
		ft_print_error("malloc error"); //
	y = 0;
	while (str[i] && str[i] != ' ')
		info[y++] = str[i++];
	info[y] = '\0';
	while (str[i] == ' ')
		i++;
	if (str[i] != '\0')
	{
		printf("error\n format not respected\n");
		//ici faire quelque chose
	}
	return (info);
}

void	ft_put_info(char *id, char *info, t_data *data)
{
	if (ft_compare(id, "NO") == 1)
		data->no = info;
	if (ft_compare(id, "SO") == 1)
		data->so = info;
	if (ft_compare(id, "WE") == 1)
		data->we = info;
	if (ft_compare(id, "EA") == 1)
		data->ea = info;
	if (info == NULL)
	{
		printf("Error\n");
		printf("No path for texture :%s\n", id);
		free(id);
		exit(0); // changer pour la fonction qui vas tout free
	}
	printf("%s : %s\n", id, info); //
}

bool	ft_get_texture2(char *str, t_data *data)
{
	int		i;
	char	*id;
	char	*info;
	
	i = 0;
	while (str[i] && str[i] == ' ')
		i++;
	id = ft_get_id(str, &i);
	printf("id: %s\n", id); // effacer plus tard
	info = ft_get_info(str, i);
	if (ft_compare(id, "NO") == 1 || ft_compare(id, "SO") == 1
		|| ft_compare(id, "WE") == 1 || ft_compare(id, "EA") == 1)
		ft_put_info(id, info, data);
	else if (ft_compare(id, "C") == 1 || ft_compare(id, "F") == 1)
		ft_extract_rgb(id, info, data);
	else
	{
		printf("Error\n");
		printf("%s: is not a correct identifier", id);
		free(id);
		if (info != NULL)
			free(info);
		exit (0); // changer par la fonction qui vas tout free
	}
	free(id);
	return (true);
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
			if (ft_get_texture2(str[i], data) == false)
				break ;
			flag++;
		}
		i++;
	}
	if (flag != 6)
	{
		ft_free_str_map(str);
		exit(0);
		//free_and_exit(data);
	}
	return (i);
}
