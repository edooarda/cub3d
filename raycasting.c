/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 12:07:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/29 18:36:15 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// TODO: VERIFICAR AS FUNCOES DAQUI

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

float	vertical_intersection(t_game *game, float angle) // vertical intersection
{
	float	x;
	float	y;
	float	x_step;
	float	y_step;
	int		pixel;
	float	distance;

	x_step = cell_size;
	y_step = cell_size / tan(angle);
	x = floor(game->player->pos_x / cell_size) * cell_size;
	if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2))
	{
		x += cell_size;
		pixel = -1;
		x_step *= -1;
	}
	else
	{
		x_step *= -1;
		pixel = 1;
	}
	y = game->player->pos_y + (x - game->player->pos_x) / tan(angle);
	if (((angle > 0 && angle < M_PI) && y_step < 0) || ((angle < 0 && angle > M_PI) && y_step > 0))
		y_step *= -1;
	while (wall_hit(x - pixel, y, game))
	{
		x += x_step;
		y += y_step;
	}
	distance = sqrt(((x - game->player->pos_x) * (x - game->player->pos_x)) + ((y - game->player->pos_y) * (y - game->player->pos_y)));
	return (distance);
}

float	horizontal_intersection(t_game *game, float angle) // horizontal intersection
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
		y_step *= -1;
	}
	else
	{
		y_step *= -1;
		pixel = 1;
	}
	x = game->player->pos_x + (y - game->player->pos_y) / tan(angle);
	if ((((angle < (M_PI / 2)) && angle > (3 * M_PI) / 2) && x_step > 0) || (((angle > (M_PI / 2)) && angle < (3 * M_PI) / 2) && x_step < 0))
		x_step *= -1;
	while (wall_hit(x, y - pixel, game))
	{
		x += x_step;
		y += y_step;
	}
	distance = sqrt(((x - game->player->pos_x) * (x - game->player->pos_x)) + ((y - game->player->pos_y) * (y - game->player->pos_y)));
	return (distance);
}



// int	unit_circle(float angle, char c)	// check the unit circle
// {
// 	if (c == 'x')
// 	{
// 		if (angle > 0 && angle < M_PI)
// 			return (1);
// 	}
// 	else if (c == 'y')
// 	{
// 		if (angle > (M_PI / 2) && angle < (3 * M_PI) / 2)
// 			return (1);
// 	}
// 	return (0);
// }

// int	inter_check(float angle, float *inter, float *step, int is_horizon)	// check the intersection
// {
// 	if (is_horizon)
// 	{
// 		if (angle > 0 && angle < M_PI)
// 		{
// 			*inter += cell_size;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	else
// 	{
// 		if (!(angle > M_PI / 2 && angle < 3 * M_PI / 2)) 
// 		{
// 			*inter += cell_size;
// 			return (-1);
// 		}
// 		*step *= -1;
// 	}
// 	return (1);
// }

// float	get_h_inter(t_game *mlx, float angl)	// get the horizontal intersection
// {
// 	float	h_x;
// 	float	h_y;
// 	float	x_step;
// 	float	y_step;
// 	int		pixel;

// 	y_step = cell_size;
// 	x_step = cell_size / tan(angl);
// 	h_y = floor(mlx->player->pos_y / cell_size) * cell_size;
// 	pixel = inter_check(angl, &h_y, &y_step, 1);
// 	h_x = mlx->player->pos_x + (h_y - mlx->player->pos_y) / tan(angl);
// 	if ((unit_circle(angl, 'y') && x_step > 0) || (!unit_circle(angl, 'y') && x_step < 0)) // check x_step value
// 		x_step *= -1;
// 	while (wall_hit(h_x, h_y - pixel, mlx)) // check the wall hit whit the pixel value
// 	{
// 		h_x += x_step;
// 		h_y += y_step;
// 	}
// 	return (sqrt(pow(h_x - mlx->player->pos_x, 2) + pow(h_y - mlx->player->pos_y, 2))); // get the distance
// }

// float	get_v_inter(t_game *mlx, float angl)	// get the vertical intersection
// {
// 	float	v_x;
// 	float	v_y;
// 	float	x_step;
// 	float	y_step;
// 	int		pixel;

// 	x_step = cell_size; 
// 	y_step = cell_size * tan(angl);
// 	v_x = floor(mlx->player->pos_x / cell_size) * cell_size;
// 	pixel = inter_check(angl, &v_x, &x_step, 0); // check the intersection and get the pixel value
// 	v_y = mlx->player->pos_y + (v_x - mlx->player->pos_x) * tan(angl);
// 	if ((unit_circle(angl, 'x') && y_step < 0) || (!unit_circle(angl, 'x') && y_step > 0)) // check y_step value
// 		y_step *= -1;
// 	while (wall_hit(v_x - pixel, v_y, mlx)) // check the wall hit whit the pixel value
// 	{
// 		v_x += x_step;
// 		v_y += y_step;
// 	}
// 	return (sqrt(pow(v_x - mlx->player->pos_x, 2) + pow(v_y - mlx->player->pos_y, 2))); // get the distance
// }




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
		// inter_horizon = get_h_inter(game, translater_angle(game->ray->angle)); // get the horizontal intersection
		// inter_vert = get_v_inter(game, translater_angle(game->ray->angle)); // get the vertical intersection
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
