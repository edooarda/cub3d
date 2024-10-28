/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 12:07:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/28 18:09:21 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	game(void *param)
{
	int		x;
	t_game	*game;

	game = param;
	x = 0;
	while (x < WIDTH)
	{
		game->ray.view_x = 2 * x / WIDTH - 1;
		game->ray.direction_x = game->player.direction_x + game->player.angle_x * game->ray.view_x;
		game->ray.direction_y = game->player.direction_y + game->player.angle_y * game->ray.view_x;
		x++;
	}
}

void	init_ray(t_ray *ray)
{
	ray->map_x = 0;
	ray->map_y = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->side = 0;
	ray->wall = 0;
	ray->view_x = 0.0;
	ray->direction_x = 0.0;
	ray->direction_y = 0.0;
	ray->distance_x = 0.0;
	ray->distance_y= 0.0;
	ray->delta_distance_x = 0.0;
	ray->delta_distance_y = 0.0;
	ray->wall_distance = 0.0;
	ray->line_height = 0;
	ray->start_line = 0;
	ray->end_line = 0;
}
