#include "../kiki/cub3d.h"

void	check_for_player(int *map, int size, t_data *data)
{
	int	i;
	int	starting_point;

	i = 0;
	starting_point = 0;
	while (i < size)
	{
		if (map[i] != 0 && map[i] != 1)
			starting_point ++;
		i++;
	}
	if (starting_point < 1)
	{
		printf("Error\nNo player inside the map\n");
		free(map);
		exit(0); //changer
	}
	if (starting_point > 1)
	{
		printf("Error\nMultiples players inside the map\n");
		free(map);
		exit(0); //changer
	}
}

void	check_bad_char(t_data *data)
{
	int	i;

	i = 0;
	while (i <= data->map_s)
	{
		if (data->map_int[i] < 0)
		{
			printf("Error\nInvalid character inside the map\n");
			free(data->map_int);
			exit(0); //changer
		}
		i++;
	}
}
