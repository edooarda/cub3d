/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:52:25 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/07 12:06:26 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	movements(t_game *game, double move_x, double move_y)
{
	double	pos_y_map;
	double	pos_x_map;
	double	new_x;
	double	new_y;

	new_x = round(game->plyr->pos_x + move_x);
	new_y = round(game->plyr->pos_y + move_y);
	pos_x_map = round(game->plyr->pos_x + move_x * 5) / cell_size;
	pos_y_map = round(game->plyr->pos_y + move_y * 5) / cell_size;
	if (game->map->map2d[(int)pos_y_map][(int)pos_x_map] != '1'
		&& game->map->map2d[game->plyr->pos_y / cell_size][(int)pos_x_map] != '1'
		&& game->map->map2d[(int)pos_y_map][game->plyr->pos_x / cell_size] != '1')
	{
		game->plyr->pos_x = new_x;
		game->plyr->pos_y = new_y;
	}
}

void	player_rotation(t_game *game)
{
	if (game->plyr->rot == RIGHT)
	{
		game->plyr->agl += rotation_speed;
		if (game->plyr->agl > G_360)
			game->plyr->agl -= G_360;
	}
	else if (game->plyr->rot == LEFT)
	{
		game->plyr->agl -= rotation_speed;
		if (game->plyr->agl < 0)
			game->plyr->agl += G_360;
	}
}

void	directions_decisions(t_game *game, double move_x, double move_y)
{
	player_rotation(game);
	if (game->plyr->left_right == RIGHT)
	{
		move_x = -sin(game->plyr->agl) * player_speed;
		move_y = cos(game->plyr->agl) * player_speed;
	}
	if (game->plyr->left_right == LEFT)
	{
		move_x = sin(game->plyr->agl) * player_speed;
		move_y = -cos(game->plyr->agl) * player_speed;
	}
	if (game->plyr->up_down == UP)
	{
		move_x = cos(game->plyr->agl) * player_speed;
		move_y = sin(game->plyr->agl) * player_speed;
	}
	if (game->plyr->up_down == DOWN)
	{
		move_x = -cos(game->plyr->agl) * player_speed;
		move_y = -sin(game->plyr->agl) * player_speed;
	}
	movements(game, move_x, move_y);
}

double	player_is_facing(t_game *game)
{
	double	facing;

	if (game->map->facing_to == 'N')
		facing = G_270;
	else if (game->map->facing_to == 'S')
		facing = G_90;
	else if (game->map->facing_to == 'E')
		facing = 0;
	else
		facing = G_180;
	return (facing);
}

void	init_player(t_game *game)
{
	game->plyr->pos_x = (game->map->p_x * cell_size) + cell_size / 2;
	game->plyr->pos_y = (game->map->p_y * cell_size) + cell_size / 2;
	game->plyr->fov_rad = (60 * M_PI) / 180;
	game->plyr->agl = player_is_facing(game);
	game->plyr->rot = 0;
	game->plyr->up_down = 0;
	game->plyr->left_right = 0;
}
