/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_elements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 16:40:27 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/06 19:24:09 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_tex(t_game *game) // will be delete
{
	game->draw->no_tex = mlx_load_png("./textures/stone_north.png");
	game->draw->so_tex = mlx_load_png("./textures/grass_south.png");
	game->draw->ea_tex = mlx_load_png("./textures/brick_east.png");
	game->draw->we_tex = mlx_load_png("./textures/wood_west.png");
}

void	draw_floor(t_game *game, int ray, int bottom_px)
{
	int	floor;

	floor = bottom_px;
	while (floor < HEIGHT)
	{
		if (ray < 0)
			return ;
		else if (ray >= WIDTH)
			return ;
		if (floor < 0)
			return ;
		else if (floor >= HEIGHT)
			return ;
		mlx_put_pixel(game->img, ray, floor, game->draw->floor);
		floor++;
	}
}

void	draw_ceiling(t_game *game, int ray, int top_px)
{
	int	ceiling;

	ceiling = 0;
	while (ceiling < top_px)
	{
		if (ray < 0)
			return ;
		else if (ray >= WIDTH)
			return ;
		mlx_put_pixel(game->img, ray, ceiling, game->draw->ceil);
		ceiling++;
	}
}

void	put_on_screen(t_game *game, int ray)
{
	double	bottom_px;
	double	top_px;

	game->ray->dist *= cos(nor_angle(game->ray->agl - game->plyr->agl));
	game->wall->wall_h = (cell_size / game->ray->dist)
		* ((WIDTH / 2) / tan(game->plyr->fov_rad / 2));
	bottom_px = (HEIGHT / 2) + (game->wall->wall_h / 2);
	top_px = (HEIGHT / 2) - (game->wall->wall_h / 2);
	if (bottom_px > HEIGHT)
		bottom_px = HEIGHT;
	if (top_px < 0)
		top_px = 0;
	game->ray->slice = ray;
	draw_ceiling(game, ray, top_px);
	draw_wall(game, top_px, bottom_px);
	draw_floor(game, ray, bottom_px);
}
