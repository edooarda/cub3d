/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:52:25 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/04 14:58:50 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	moviments(t_game *game, double move_x, double move_y)
{
	int	pos_y_map;
	int	pos_x_map;
	int	new_x;
	int	new_y;

	new_x = roundf(game->plyr->pos_x + move_x);
	new_y = roundf(game->plyr->pos_y + move_y);
	pos_x_map = new_x / cell_size;
	pos_y_map = new_y / cell_size;
	if (game->temp->map2d[pos_y_map][pos_x_map] != '1'
		&& game->temp->map2d[game->plyr->pos_y / cell_size][pos_x_map] != '1'
		&& game->temp->map2d[pos_y_map][game->plyr->pos_x / cell_size] != '1')
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
	moviments(game, move_x, move_y);
}

float	player_is_facing(t_game *game)
{
	float	facing;

	if (game->temp->facing_to == 'N')
		facing = G_360;
	else if (game->temp->facing_to == 'S')
		facing = G_90;
	else if (game->temp->facing_to == 'E')
		facing = 0;
	else
		facing = G_180;
	return (facing);
}

void	init_player(t_game *game)
{
	game->plyr->pos_x = (game->temp->p_x * cell_size) + cell_size / 2;
	game->plyr->pos_y = (game->temp->p_y * cell_size) + cell_size / 2;
	game->plyr->fov_rad = (60 * M_PI) / 180;
	game->plyr->agl = player_is_facing(game);
	game->plyr->rot = 0;
	game->plyr->up_down = 0;
	game->plyr->left_right = 0;
}
