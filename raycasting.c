/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 12:07:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/30 13:16:06 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

float	translater_angle(float angle)// to keep the angle in 0 and 360, no negative
{
	if (angle < 0)
		angle += (2 * M_PI);
	if (angle > (2 * M_PI))
		angle -= (2 * M_PI);
	return (angle);
}

int	wall_hit(float x, float y, t_game *game)
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

float	vertical_intersection(t_game *game, float angle)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;
	float	distance;

	x_step = cell_size;
	y_step = cell_size * tan(angle);
	x = floor(game->player->pos_x / cell_size) * cell_size;
	if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
	{
		x += cell_size;
		pixel = -1;
	}
	else
		pixel = 1;
	x_step *= -1;
	y = game->player->pos_y + (x - game->player->pos_x) * tan(angle);
	if (((angle > 0 && angle < M_PI) && y_step < 0) || (!(angle > 0 && angle < M_PI) && y_step > 0))
		y_step *= -1;
	while (wall_hit(x - pixel, y, game))
	{
		x += x_step;
		y += y_step;
	}
	distance = sqrt(((x - game->player->pos_x) * (x - game->player->pos_x)) + ((y - game->player->pos_y) * (y - game->player->pos_y)));
	return (distance);
}

float	horizontal_intersection(t_game *game, float angle)
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;
	float	distance;

	y_step = cell_size;
	x_step = cell_size / tan(angle);
	y = floor(game->player->pos_y / cell_size) * cell_size;
	if (angle > 0 && angle < M_PI)
	{
		y += cell_size;
		pixel = -1;
	}
	else
		pixel = 1;
	y_step *= -1;
	x = game->player->pos_x + (y - game->player->pos_y) / tan(angle);
	if (((angle > (M_PI / 2) && angle < (3 * M_PI) / 2) && x_step > 0) || (!(angle > (M_PI / 2) && angle < (3 * M_PI) / 2) && x_step < 0)) // check x_step value
		x_step *= -1;
	while (wall_hit(x, y - pixel, game))
	{
		x += x_step;
		y += y_step;
	}
	distance = sqrt(((x - game->player->pos_x) * (x - game->player->pos_x)) + ((y - game->player->pos_y) * (y - game->player->pos_y)));
	return (distance);
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
