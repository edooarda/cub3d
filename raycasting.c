/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 12:07:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/01 14:41:43 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_hit(float x, float y, t_game *game) // bonus
{
	int	x_point_map;
	int	y_point_map;

	if (x < 0 || y < 0)
		return (0);
	x_point_map = floor(x / cell_size);
	y_point_map = floor(y / cell_size);
	if (y_point_map >= game->temp->h_map || x_point_map >= game->temp->w_map)
		return (0);
	if (game->temp->map2d[y_point_map] && x_point_map <= (int)ft_strlen(game->temp->map2d[y_point_map]))
	{
		if (game->temp->map2d[y_point_map][x_point_map] == '1')
			return (0);
	}
	return (1);
}

float	translater_angle(float angle)// to keep the angle in 0 and 360, no negative
{
	if (angle < 0)
		angle += G_360;
	if (angle > G_360)
		angle -= G_360;
	return (angle);
}

float	vertical_intersection(t_game *game, float angle)
{
	game->ray->vert_x_step = cell_size;
	game->ray->vert_y_step = cell_size * tan(angle);
	game->ray->vert_x = floor(game->player->pos_x / cell_size) * cell_size;
	if (angle > G_90 && angle < G_270) // looking left mas esta entre os angulos de 90 e 270
	{
		game->ray->vert_pixel = 1;
		game->ray->vert_x_step *= -1;
	}
	else
	{
		game->ray->vert_x += cell_size;
		game->ray->vert_pixel = -1;
	}
	game->ray->vert_y = game->player->pos_y + (game->ray->vert_x - game->player->pos_x) * tan(angle);
	if (((angle > 0 && angle < G_180) && game->ray->vert_y_step < 0)
		|| (!(angle > 0 && angle < G_180) && game->ray->vert_y_step > 0))
		game->ray->vert_y_step *= -1;
	while (wall_hit(game->ray->vert_x - game->ray->vert_pixel, game->ray->vert_y, game))
	{
		game->ray->vert_x += game->ray->vert_x_step;
		game->ray->vert_y += game->ray->vert_y_step;
	}
	game->ray->distance = sqrt(((game->ray->vert_x - game->player->pos_x) * (game->ray->vert_x - game->player->pos_x))
		+ ((game->ray->vert_y - game->player->pos_y) * (game->ray->vert_y - game->player->pos_y)));
	return (game->ray->distance);
}

float	horizontal_intersection(t_game *game, float angle)
{
	game->ray->horizon_y_step = cell_size;
	game->ray->horizon_x_step = cell_size / tan(angle);
	game->ray->horizon_y = floor(game->player->pos_y / cell_size) * cell_size;
	if (angle > 0 && angle < G_180) // this represents 0 to 180
	{
		game->ray->horizon_y += cell_size;
		game->ray->horizon_pixel = -1;
	}
	else
	{
		game->ray->horizon_pixel = 1;
		game->ray->horizon_y_step *= -1; // needs to be negative to go for upper cels because the else is for 180 - 360
	}
	game->ray->horizon_x = game->player->pos_x + (game->ray->horizon_y - game->player->pos_y) / tan(angle);
	if (((angle > G_90 && angle < G_270) && game->ray->horizon_x_step > 0) || (!(angle > G_90 && angle < G_270) && game->ray->horizon_x_step < 0))
		game->ray->horizon_x_step *= -1;
	while (wall_hit(game->ray->horizon_x, game->ray->horizon_y - game->ray->horizon_pixel, game))
	{
		game->ray->horizon_x += game->ray->horizon_x_step;
		game->ray->horizon_y += game->ray->horizon_y_step;
	}
	game->ray->horizon_distance = sqrt(((game->ray->horizon_x - game->player->pos_x) * (game->ray->horizon_x - game->player->pos_x)) + ((game->ray->horizon_y - game->player->pos_y) * (game->ray->horizon_y - game->player->pos_y)));
	return (game->ray->horizon_distance);
}

void	casting_rays(t_game *game)
{
	double	inter_horizon;
	double	inter_vert;
	int		ray;

	ray = 0;
	game->ray->angle = game->player->angle - (game->player->fov_radians / 2); // start angle
	while (ray < WIDTH)
	{
		game->ray->wall = false;
		inter_horizon = horizontal_intersection(game, translater_angle(game->ray->angle));
		inter_vert = vertical_intersection(game, translater_angle(game->ray->angle));
		if (inter_vert <= inter_horizon)
			game->ray->distance = inter_vert;
		else
		{
			game->ray->distance = inter_horizon;
			game->ray->wall = true;
		}
		put_on_screen(game, ray);
		ray++;
		game->ray->angle += (game->player->fov_radians / WIDTH);
	}
}
