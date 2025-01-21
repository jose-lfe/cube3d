/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:15:49 by jose-lfe          #+#    #+#             */
/*   Updated: 2025/01/21 11:17:19 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../kiki/cub3d.h"

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

int	ft_fill_map_int(char c)
{
	if (c == '1')
		return (1);
	else if (c == '0')
		return (0);
	else if (c == ' ')
		return (6);
	else if (c == 'N')
		return (2);
	else if (c == 'S')
		return (3);
	else if (c == 'E')
		return (4);
	else if (c == 'W')
		return (5);
	else
		return (-1);
}

char	*ft_fill_map_char2(int	check)
{
	if (check == 0)
		return ('0');
	if (check == 1)
		return ('1');
	if (check == 2)
		return ('N');
	if (check == 3)
		return ('S');
	if (check == 4)
		return ('E');
	if (check == 5)
		return ('W');
	else
		return (' ');
}

int	ft_fill_map_char(t_data *data, int i, int x)
{
	int	j;

	j = 0;
	data->map[i] = malloc((data->map_x + 1) * sizeof(char));
	if (data->map[i] == NULL)
		return (-1);
	while (j < data->map_x)
	{
		data->map[i][j] = ft_fill_map_char2(data->map_int[x]);
		j++;
		x++;
	}
	data->map[i][j] = '\0';
	return (x);
}

void	convert_map_int_to_char(t_data *data)
{
	int	i;
	int	x;

	i  = 0;
	x = 0;
	data->map = malloc((data->map_y + 1) * sizeof(char *));
	if (data->map == NULL)
		exit(0); // changer
	while (i < data->map_y)
	{
		x = ft_fill_map_char(data, i, x);
		if (x == 0)
		{
			ft_free_str_map(data->map);
			exit(0); //changer
		}
		i++;
	}
	data->map[i] = NULL;
	i = 0;
	printf("new map\n");
	while (data->map[i])
		printf("%s\n", data->map[i++]);
	free(data->map_int);
}

void	convert_map2(char **str, int i, t_data *data)
{
	data->map_x = find_map_x(str, i);
	data->map_s = data->map_x * data->map_y;
	data->map_int = malloc(data->map_s * sizeof(int));
}

void	convert_map(char **str, int	i, t_data *data)
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
