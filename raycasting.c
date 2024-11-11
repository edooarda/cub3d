/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycasting.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/28 12:07:28 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/11 15:34:27 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	wall_hit(double x, double y, t_game *game)
{
	double	x_point_map;
	double	y_point_map;

	if (x < 0 || y < 0)
		return (0);
	x_point_map = floor(x / CELL_SIZE);
	y_point_map = floor(y / CELL_SIZE);
	if (y_point_map >= game->map->h_map || x_point_map >= game->map->w_map)
		return (0);
	if (game->map->map2d[(int)y_point_map]
		&& x_point_map <= ft_strlen(game->map->map2d[(int)y_point_map]))
	{
		if (game->map->map2d[(int)y_point_map][(int)x_point_map] == '1')
			return (0);
	}
	return (1);
}

// 2*M_PI is 360 degrees
double	nor_angle(double angle)
{
	if (angle < 0)
		angle += 2 * M_PI;
	if (angle > 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

// 3*M_PI/2 is 270 degrees
// M_PI is 180 degrees
// M_PI/2 is 90 degrees
double	vert_inter(t_game *g, t_ray *ray, double agl)
{
	ray->v_x_step = CELL_SIZE;
	ray->v_y_step = CELL_SIZE * tan(agl);
	ray->v_x = floor(g->plyr->pos_x / CELL_SIZE) * CELL_SIZE;
	if (agl > M_PI / 2 && agl < 3 * M_PI / 2)
	{
		ray->v_px = 1;
		ray->v_x_step *= -1;
	}
	else
	{
		ray->v_x += CELL_SIZE;
		ray->v_px = -1;
	}
	ray->v_y = g->plyr->pos_y + (ray->v_x - g->plyr->pos_x) * tan(agl);
	if (((agl > 0 && agl < M_PI) && ray->v_y_step < 0)
		|| (!(agl > 0 && agl < M_PI) && ray->v_y_step > 0))
		ray->v_y_step *= -1;
	while (wall_hit(ray->v_x - ray->v_px, ray->v_y, g))
	{
		ray->v_x += ray->v_x_step;
		ray->v_y += ray->v_y_step;
	}
	ray->vdis = sqrt(((ray->v_x - g->plyr->pos_x) * (ray->v_x - g->plyr->pos_x))
			+ ((ray->v_y - g->plyr->pos_y) * (ray->v_y - g->plyr->pos_y)));
	return (ray->vdis);
}

// 3*M_PI/2 is 270 degrees
// M_PI is 180 degrees
// M_PI/2 is 90 degrees
double	horizon_inter(t_game *g, t_ray *ray, double agl)
{
	ray->h_y_step = CELL_SIZE;
	ray->h_x_step = CELL_SIZE / tan(agl);
	ray->h_y = floor(g->plyr->pos_y / CELL_SIZE) * CELL_SIZE;
	if (agl > 0 && agl < M_PI)
	{
		ray->h_y += CELL_SIZE;
		ray->h_px = -1;
	}
	else
	{
		ray->h_px = 1;
		ray->h_y_step *= -1;
	}
	ray->h_x = g->plyr->pos_x + (ray->h_y - g->plyr->pos_y) / tan(agl);
	if (((agl > M_PI / 2 && agl < 3 * M_PI / 2) && ray->h_x_step > 0)
		|| (!(agl > M_PI / 2 && agl < 3 * M_PI / 2) && ray->h_x_step < 0))
		ray->h_x_step *= -1;
	while (wall_hit(ray->h_x, ray->h_y - ray->h_px, g))
	{
		ray->h_x += ray->h_x_step;
		ray->h_y += ray->h_y_step;
	}
	ray->hdis = sqrt(((ray->h_x - g->plyr->pos_x) * (ray->h_x - g->plyr->pos_x))
			+ ((ray->h_y - g->plyr->pos_y) * (ray->h_y - g->plyr->pos_y)));
	return (ray->hdis);
}

void	casting_rays(t_game *game)
{
	double	h_inter;
	double	v_inter;
	int		ray;

	ray = 0;
	game->ray->agl = game->plyr->agl - (game->plyr->fov_rad / 2);
	while (ray < WIDTH)
	{
		game->ray->n_s_wall = false;
		h_inter = horizon_inter(game, game->ray, nor_angle(game->ray->agl));
		v_inter = vert_inter(game, game->ray, nor_angle(game->ray->agl));
		if (v_inter <= h_inter)
			game->ray->dist = v_inter;
		else
		{
			game->ray->dist = h_inter;
			game->ray->n_s_wall = true;
		}
		put_on_screen(game, ray);
		ray++;
		game->ray->agl += (game->plyr->fov_rad / WIDTH);
	}
}
