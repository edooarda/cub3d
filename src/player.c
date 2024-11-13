/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:52:25 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/13 11:30:37 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	movements(t_game *g, double move_x, double move_y)
{
	double	plyr_y_map;
	double	plyr_x_map;
	double	new_x;
	double	new_y;

	new_x = round(g->plyr->pos_x + move_x);
	new_y = round(g->plyr->pos_y + move_y);
	plyr_x_map = round(g->plyr->pos_x + move_x * HIT_BOX) / CELL_SIZE;
	plyr_y_map = round(g->plyr->pos_y + move_y * HIT_BOX) / CELL_SIZE;
	if (g->map->map2d[(int)plyr_y_map][(int)plyr_x_map] != '1'
		&& g->map->map2d[g->plyr->pos_y / CELL_SIZE][(int)plyr_x_map] != '1'
		&& g->map->map2d[(int)plyr_y_map][g->plyr->pos_x / CELL_SIZE] != '1')
	{
		g->plyr->pos_x = new_x;
		g->plyr->pos_y = new_y;
	}
}

// 2*M_PI is 360 degrees
void	player_rotation(t_game *game)
{
	if (game->plyr->rot == RIGHT)
	{
		game->plyr->agl += ROTATION_SPEED;
		if (game->plyr->agl > 2 * M_PI)
			game->plyr->agl -= 2 * M_PI;
	}
	else if (game->plyr->rot == LEFT)
	{
		game->plyr->agl -= ROTATION_SPEED;
		if (game->plyr->agl < 0)
			game->plyr->agl += 2 * M_PI;
	}
}

void	directions_decisions(t_game *game, double move_x, double move_y)
{
	player_rotation(game);
	if (game->plyr->left_right == RIGHT)
	{
		move_x = -sin(game->plyr->agl) * PLAYER_SPEED;
		move_y = cos(game->plyr->agl) * PLAYER_SPEED;
	}
	if (game->plyr->left_right == LEFT)
	{
		move_x = sin(game->plyr->agl) * PLAYER_SPEED;
		move_y = -cos(game->plyr->agl) * PLAYER_SPEED;
	}
	if (game->plyr->up_down == UP)
	{
		move_x = cos(game->plyr->agl) * PLAYER_SPEED;
		move_y = sin(game->plyr->agl) * PLAYER_SPEED;
	}
	if (game->plyr->up_down == DOWN)
	{
		move_x = -cos(game->plyr->agl) * PLAYER_SPEED;
		move_y = -sin(game->plyr->agl) * PLAYER_SPEED;
	}
	movements(game, move_x, move_y);
}

// 3*M_PI/2 is 270 degrees
// M_PI is 180 degrees
// M_PI/2 is 90 degrees
double	player_is_facing(t_game *game)
{
	double	facing;

	if (game->map->facing_to == 'N')
		facing = 3 * M_PI / 2;
	else if (game->map->facing_to == 'S')
		facing = M_PI / 2;
	else if (game->map->facing_to == 'E')
		facing = 0;
	else
		facing = M_PI;
	return (facing);
}

void	init_player(t_game *game)
{
	game->plyr->pos_x = (game->map->p_x * CELL_SIZE) + CELL_SIZE / 2;
	game->plyr->pos_y = (game->map->p_y * CELL_SIZE) + CELL_SIZE / 2;
	game->plyr->fov_rad = (60 * M_PI) / 180;
	game->plyr->agl = player_is_facing(game);
	game->plyr->rot = 0;
	game->plyr->up_down = 0;
	game->plyr->left_right = 0;
}
