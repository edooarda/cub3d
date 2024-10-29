/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   player.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 13:52:25 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/29 14:00:58 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
