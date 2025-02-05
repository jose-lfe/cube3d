/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kdroz <kdroz@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 12:42:45 by kdroz             #+#    #+#             */
/*   Updated: 2025/02/05 15:15:58 by kdroz            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	key_press(int key, t_game *game)
{
	t_player	*player;

	player = &game->player;
	if (key == KEY_A)
		player->key_left = true;
	if (key == KEY_D)
		player->key_right = true;
	if (key == KEY_W)
		player->key_up = true;
	if (key == KEY_S)
		player->key_down = true;
	if (key == KEY_LEFT)
		player->left_rotate = true;
	if (key == KEY_RIGHT)
		player->right_rotate = true;
	if (key == KEY_ESC)
	{
		ft_free_all_game(game, NULL);
	}
	return (0);
}

int	key_release(int key, t_player *player)
{
	if (key == KEY_A)
		player->key_left = false;
	if (key == KEY_D)
		player->key_right = false;
	if (key == KEY_W)
		player->key_up = false;
	if (key == KEY_S)
		player->key_down = false;
	if (key == KEY_LEFT)
		player->left_rotate = false;
	if (key == KEY_RIGHT)
		player->right_rotate = false;
	return (0);
}

void	player_rotation(t_player *player)
{
	if (player->left_rotate)
		player->angle -= player->angle_speed;
	if (player->right_rotate)
		player->angle += player->angle_speed;
	if (player->angle > 2 * PI)
		player->angle -= 2 * PI;
	if (player->angle < 0)
		player->angle += 2 * PI;
}

void	player_movement(t_game *game, t_player *p,
			float cos_angle, float sin_angle)
{
	if (p->key_up)
	{
		p->new_x += cos_angle * p->speed;
		p->new_y += sin_angle * p->speed;
	}
	if (p->key_down)
	{
		p->new_x -= cos_angle * p->speed;
		p->new_y -= sin_angle * p->speed;
	}
	if (p->key_left)
	{
		p->new_x += sin_angle * p->speed;
		p->new_y -= cos_angle * p->speed;
	}
	if (p->key_right)
	{
		p-> new_x -= sin_angle * p->speed;
		p-> new_y += cos_angle * p->speed;
	}
	if (!touch(p->new_x, p->new_y, game))
	{
		p->x = p->new_x;
		p->y = p->new_y;
	}
}

void	move_player(t_game *game, t_player *player)
{
	float	cos_angle;
	float	sin_angle;

	cos_angle = cos(player->angle);
	sin_angle = sin(player->angle);
	player->new_x = player->x;
	player->new_y = player->y;
	player_rotation(player);
	player_movement(game, player, cos_angle, sin_angle);
}
