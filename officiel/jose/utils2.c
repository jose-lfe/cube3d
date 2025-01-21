#include "../kiki/cub3d.h"

float	find_player_x(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != '1')
				return (x);
			x++;
		}
		y++;
	}
}

float	find_player_y(char **map)
{
	int	x;
	int	y;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] != '0' && map[y][x] != '1')
				return (y);
			x++;
		}
		y++;
	}
}
