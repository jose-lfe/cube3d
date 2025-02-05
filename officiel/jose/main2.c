/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:15:49 by jose-lfe          #+#    #+#             */
/*   Updated: 2025/02/05 15:13:44 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_eof(char **str, t_data *data, int i)
{
	while (str[i] && ft_start_map(str[i]) == 1)
		i++;
	if (str[i] != NULL)
	{
		ft_free_str_map(str);
		ft_free_all("the map is not the end of the file\n", data);
	}
}

void	ft_print_map(char **str, t_data *data)
{
	int	i;

	i = 0;
	i = get_texture(str, data);
	check_eof(str, data, i);
	convert_map(str, i, data);
	ft_free_str_map(str);
	check_bad_char(data);
	check_for_player(data->map_int, data->map_s, data);
	convert_map_int_to_char(data);
	check_map(data);
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

/*int	main(int ac, char **av)
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
*/