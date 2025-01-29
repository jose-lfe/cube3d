/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:15:49 by jose-lfe          #+#    #+#             */
/*   Updated: 2025/01/28 16:36:11 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kiki/cub3d.h"

void	ft_init_mlx(t_data *data)
{
	printf("all clear\n");
	ft_free_all(NULL, data);
}

void	ft_print_map(char **str, t_data *data)
{
	int		i;
	int		d;

	i = 0;
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
	i = get_texture(str, data);
	convert_map(str, i, data);
	ft_printf("mapx = %i\n", data->map_x);
	ft_printf("mapy = %i\n", data->map_y);
	ft_printf("maps = %i\n", data->map_s);
	d = 0;
	while (d < data->map_s)
	{
		if (d % data->map_x == 0)
			ft_printf("\n");
		ft_printf("%i", data->map_int[d]);
		d++;
	}
	ft_free_str_map(str);
	check_bad_char(data);
	check_for_player(data->map_int, data->map_s, data);
	convert_map_int_to_char(data);
}

void	ft_get_map(int fd, char *test, t_data *data)
{
	char	*tmp;
	char	*str;
	char	**map;
	char	*newstr;

	str = test;
	tmp = get_next_line(fd);
	while (tmp != NULL)
	{
		newstr = ft_strjoin(str, tmp);
		free(str);
		str = newstr;
		free(tmp);
		tmp = get_next_line(fd);
	}
	map = ft_split(str, '\n');
	free(str);
	ft_print_map(map, data);
	close(fd);
	ft_init_mlx(data);
}

void	check_file_name(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len <= 4 || ft_strncmp(str + len - 4, ".cub", 4) != 0)
	{
		ft_printf("file must be in format : *.cub\n");
		exit (0);
	}
}

int	main(int ac, char **av)
{
	int		fd;
	char	*tmp;
	t_data	data;

	fd = 0;
	data = init_data();
	if (ac != 2)
		ft_print_error("Single argument required (*.cub)");
	check_file_name(av[1]);
	fd = open(av[1], fd, O_RDONLY);
	if (fd == -1)
		ft_print_error("Error opening file");
	tmp = get_next_line(fd);
	if (!tmp)
		ft_print_error("empty map");
	ft_get_map(fd, tmp, &data);
	return (0);
}
