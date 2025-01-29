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

void	ft_get_player_data(char c, int y, int x, t_data *data)
{
	data->player_y = (float)y;
	data->player_x = (float)x;
	if (c == 'N')
		data->player_angle = 1.0;
	else if (c == 'W')
		data->player_angle = 0.75;
	else if (c == 'S')
		data->player_angle = 0.5;
	else
		data->player_angle = 0.25;
	data->map[y][x] = '0';
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
		if (data->map[i][j] > 65 && data->map[i][j] < 90)
		{
			ft_get_player_data(data->map[i][j], i, j, data);
		}
		j++;
		x++;
	}
	data->map[i][j] = '\0';
	return (x);
}

char	ft_fill_map_char2(int check)
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
