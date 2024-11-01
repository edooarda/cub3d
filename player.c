/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:52:25 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/01 10:12:14 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	moviments(t_game *game, double move_x, double move_y)
{
	int	pos_y_map;
	int	pos_x_map;
	int	new_x;
	int	new_y;

	new_x = roundf(game->player->pos_x + move_x);
	new_y = roundf(game->player->pos_y + move_y);
	pos_x_map = new_x / cell_size;
	pos_y_map = new_y / cell_size;
	if (game->temp->map2d[pos_y_map][pos_x_map] != '1' && game->temp->map2d[game->player->pos_y / cell_size][pos_x_map] != '1' && game->temp->map2d[pos_y_map][game->player->pos_x / cell_size] != '1') // check diagonal hit to the wall
	{
		game->player->pos_x = new_x;
		game->player->pos_y = new_y;
	}
}
void	directions_decisions(t_game *game, double move_x, double move_y)
{
	if (game->player->rotation == RIGHT)
	{
		game->player->angle += rotation_speed;
		if (game->player->angle > G_360) //(2 * M_PI) represents 360graus
			game->player->angle -= G_360; // para manter o angulo dentro do escopo de 0 a 360
	}
	else if(game->player->rotation == LEFT)
	{
		game->player->angle -= rotation_speed;
		if (game->player->angle < 0)
			game->player->angle += G_360;
	}
	if (game->player->left_right == RIGHT)
	{
		move_x = -sin(game->player->angle) * player_speed;
		move_y = cos(game->player->angle) * player_speed;
	}
	if (game->player->left_right == LEFT)
	{
		move_x = sin(game->player->angle) * player_speed;
		move_y = -cos(game->player->angle) * player_speed;
	}
	if (game->player->up_down == UP)
	{
		move_x = cos(game->player->angle) * player_speed;
		move_y = sin(game->player->angle) * player_speed;
	}
	if (game->player->up_down == DOWN)
	{
		move_x = -cos(game->player->angle) * player_speed;
		move_y = -sin(game->player->angle) * player_speed;
	}
	moviments(game, move_x, move_y);
}

void	init_player(t_game *game)
{
	game->player->pos_x = game->temp->p_x * cell_size + cell_size / 2;
	game->player->pos_y = game->temp->p_y * cell_size + cell_size / 2;
	game->player->fov_radians = (60 * M_PI) / 180;
	game->player->angle = M_PI;
	game->player->rotation = 0;
	game->player->up_down = 0;
	game->player->left_right = 0;
}
