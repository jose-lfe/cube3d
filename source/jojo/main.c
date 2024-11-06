/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:15:49 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/11/06 04:27:28 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	start_of_map(char **str)
{
	int	i;

	i = 0;
	
}

int	find_map_x(char **str, int i)
{
	int	x;
	int	tmp;

	x = 0;
	while (str[i])
	{
		tmp = 0;
		while (str[i][tmp])
			tmp++;
		if (tmp > x)
			x = tmp;
		i++;
	}
	return (x);
}

int	ft_fill_map(char c)
{
	if (c == '1')
		return (1);
	else if (c == '0')
		return (0);
	else
		return (0);
}

void	convert_map(char **str, int	i, t_data *data)
{
	int		y;
	int		tmp;
	int		d;
	
	y = 1;
	d = 0;
	while (str[i + y])
		y ++;
	data->map_y = y;
	data->map_x = find_map_x(str, i);
	data->map_s = data->map_x * data->map_y;
	data->map = malloc(data->map_s * sizeof(int));
	while (str[i])
	{
		tmp = 0;
		while (tmp < data->map_x)
			data->map[d++] = ft_fill_map(str[i][tmp++]);
		i++;
	}
}

int	get_info2(char *str, int flag, t_data *data)
{
	int	len;
	
	len = 0;
	while (str[len] != ' ' && str[len] != '\0')
		len++;
	if (len == 2 && ft_strncmp(str + len, "NO", 2) == 0)
		
}

int	get_info(char **str, t_data *data)
{
	int	flag;
	int	i;
	int	j;

	flag = 0;
	i = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j] == ' ')
			j++;
		if (str[i][j] != '\0')
			flag = get_info2(str[i] + j, flag, data);
	}
	return (flag);
}

void	ft_print_map(char **str, t_data *data)
{
	int		i;
	int		d;
	int		flag;

	i = 0;
	while (str[i])
	{
		ft_printf("%s\n", str[i]);
		i++;
	}
	flag = get_texture(str, data);
	i = 6;
	i = start_of_map(str);
	convert_map(str, i, data);
	ft_printf("mapx = %i\n", data->map_x);
	ft_printf("mapy = %i\n", data->map_y);
	ft_printf("maps = %i\n", data->map_s);
	d = 0;
	while (d < data->map_s)
	{
		if (d % data->map_x == 0)
			ft_printf("\n");
		ft_printf("%i", data->map[d]);
		d++;
	}
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
	// if (check_map(map) == 1)
	// {
	// 	ft_free_map(map);
	// 	return ;
	// }
	close(fd);
	//ft_init_mlx(map);
}

void	check_file_name(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (len <= 4 || ft_strncmp(str + len - 4, ".cub", 4) != 0)
	{
		ft_printf("file must be in format : *.ber\n");
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
