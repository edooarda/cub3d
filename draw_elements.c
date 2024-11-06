/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_elements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 16:40:27 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/06 15:11:20 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void init_tex(t_game *game)
{
	game->draw->no_tex = mlx_load_png("./textures/stone_north.png");
	game->draw->so_tex = mlx_load_png("./textures/grass_south.png");
	game->draw->ea_tex =  mlx_load_png("./textures/brick_east.png");
	game->draw->we_tex = mlx_load_png("./textures/wood_west.png");
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
		if (ray < 0) // check the x position
			return ;
		else if (ray >= WIDTH)
			return ;
		mlx_put_pixel(game->img, ray, ceiling, game->draw->ceil);
		ceiling++;
	}
}

mlx_texture_t *pick_texture(t_game *game, int flag)
{
	game->ray->agl = nor_angle(game->ray->agl); // normalize the angle
	if (flag == 0)
	{
		if (game->ray->agl > G_90 && game->ray->agl < G_270)
		{
			return (game->draw->we_tex); // west wall
		}
		else
		{
			return (game->draw->ea_tex); // east wall
		}
	}
	else
	{
		if (game->ray->agl > 0 && game->ray->agl < G_180)
		{
			return (game->draw->so_tex);// south wall
		}
		else
		{
			return (game->draw->no_tex); // north wall
		}
	}
}

int	get_pixel(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

void	draw_wall(t_game *game, int t_pix, int b_pix, double wall_h)
{
	double			x_o;//x orientation
	double			y_o;//y orientation
	mlx_texture_t	*tex;
	uint32_t		*tex_px;
	double			factor;

	tex = pick_texture(game, game->ray->wall);
	tex_px = (uint32_t *)tex->pixels;
	factor = (double)tex->height / wall_h;
	if (game->ray->wall == true)
		x_o = (int)fmodf((game->ray->h_x * \
			(tex->width / cell_size)), tex->width);
	else
		x_o = (int)fmodf((game->ray->v_y * \
		(tex->width / cell_size)), tex->width);
	y_o = (t_pix - (HEIGHT / 2) + (wall_h / 2)) * factor;
	if (y_o < 0)
		y_o = 0;
	while (t_pix < b_pix)
	{
		if (game->ray->index < 0)
			return ;
		else if (game->ray->index >= WIDTH)
			return ;
		if (t_pix < 0)
			return ;
		else if (t_pix >= HEIGHT)
			return ;
		mlx_put_pixel(game->img, game->ray->index, t_pix, get_pixel \
		(tex_px[(int)y_o * tex->width + (int)x_o]));
		y_o += factor;
		t_pix++;
	}
}

void	put_on_screen(t_game *game, int ray)
{
	double	wall_height;
	double	bottom_px;
	double	top_px;

	game->ray->dist *= cos(nor_angle(game->ray->agl - game->plyr->agl));
	wall_height = (cell_size / game->ray->dist)
		* ((WIDTH / 2) / tan(game->plyr->fov_rad / 2));
	bottom_px = (HEIGHT / 2) + (wall_height / 2);
	top_px = (HEIGHT / 2) - (wall_height / 2);
	if (bottom_px > HEIGHT)
		bottom_px = HEIGHT;
	if (top_px < 0)
		top_px = 0;
	game->ray->index = ray;
	draw_floor(game, ray, bottom_px);
	// draw_floor_ceiling(game, ray, top_px, bottom_px);
	draw_wall(game, top_px, bottom_px, wall_height);
	draw_ceiling(game, ray, top_px);
}
