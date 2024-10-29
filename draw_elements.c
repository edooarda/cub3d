/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_elements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 16:40:27 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/29 18:22:13 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_game *mlx, int flag)// get the color of the wall
{
	mlx->ray->angle = translater_angle(mlx->ray->angle); // normalize the angle
	if (flag == 0)
	{
		if (mlx->ray->angle > M_PI / 2 && mlx->ray->angle < 3 * (M_PI / 2))
			return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (mlx->ray->angle > 0 && mlx->ray->angle < M_PI)
			return (0xF5F5F5FF); // south wall
		else
			return (0xF5F5F5FF); // north wall
	}
}

void	draw_floor(t_game *game, int ray, int bottom_px)
{
	int	floor;

	floor = bottom_px;
	while (floor < HEIGHT)
	{
		if (ray < 0) // check the x position
			return ;
		else if (ray >= WIDTH)
			return ;
		if (floor < 0) // check the y position
			return ;
		else if (floor >= HEIGHT)
			return ;
		mlx_put_pixel(game->img, ray, floor, 0xB99470FF);
		floor++;
	}
}

void	draw_ceiling(t_game *game, int ray, int top_px)
{
	int	ceiling;

	ceiling = 0;
	while (ceiling < top_px)
	{
		if (ray < 0) // check the x position
			return ;
		else if (ray >= WIDTH)
			return ;
		mlx_put_pixel(game->img, ray, ceiling, 0x89CFF3FF);
		ceiling++;
	}
}

// void	draw_wall (t_game *game, int ray, int top_px, int bottom_px)
// {
// 	// vai ser as texturas e nao cor
// 	int color;

// 	color = get_color(game, game->ray->wall);
// 	while (top_px < bottom_px) // change to go until reach the WIDTH
// 	{
// 		if (ray < 0) // check the x position
// 			return ;
// 		else if (ray >= WIDTH)
// 			return ;
// 		if (top_px < 0) // check the y position
// 			return ;
// 		else if (top_px >= WIDTH)
// 			return ;
// 		mlx_put_pixel(game->img, ray, top_px, color);
// 		top_px++;
// 	}
// }

void	put_on_screen(t_game *game, int ray)
{
	double	wall_height;
	double	bottom_px;
	double	top_px;

	game->ray->distance *= cos(translater_angle(game->ray->angle - game->player->angle)); // verificar a necessidade do translate angle
	wall_height = (cell_size / game->ray->distance) * ((WIDTH / 2) / tan(game->player->fov_radians / 2));
	bottom_px = (HEIGHT / 2) + (wall_height / 2);
	top_px = (HEIGHT / 2) - (wall_height / 2);
	if (bottom_px > HEIGHT)
		bottom_px = HEIGHT;
	if (top_px < 0)
		top_px = 0;
	// draw_wall(game, ray, top_px, bottom_px);
	draw_ceiling(game, ray, top_px);
	draw_floor(game, ray, bottom_px);
}
