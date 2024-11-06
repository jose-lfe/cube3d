/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-lfe <jose-lfe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:16:55 by jose-lfe          #+#    #+#             */
/*   Updated: 2024/11/06 03:51:44 by jose-lfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include "libft.h"
# include "get_next_line_bonus.h"
# include "ft_printf.h"

typedef struct s_map
{
}	t_map;

typedef struct s_data
{
	int		map_x;
	int		map_y;
	int		map_s;
	int		*map;
	void	*mlx;
	void	*win;
	void	*NO_p;
	void	*SO_p;
	void	*WE_p;
	void	*EA_p;
	int		*NO_i;
	int		*SO_i;
	int		*WE_i;
	int		*EA_i;
	int		F;
	int		C;
}	t_data;

//jojo/error.c
void	ft_print_error(char *str);

//jojo/utils.c
t_data	init_data(void);

#endif