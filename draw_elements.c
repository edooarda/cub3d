/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_elements.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/29 16:40:27 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/05 14:39:51 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_color(t_game *mlx, int flag)// get the color of the wall
{
	mlx->ray->agl = nor_angle(mlx->ray->agl); // normalize the angle
	if (flag == 0)
	{
		if (mlx->ray->agl > G_90 && mlx->ray->agl < G_270)
			return (0xC7CC29FF);
			// return (0xB5B5B5FF); // west wall
		else
			return (0xB5B5B5FF); // east wall
	}
	else
	{
		if (mlx->ray->agl > 0 && mlx->ray->agl < G_180)
			return (0x4634EBFF); // south wall
			// return (0xF5F5F5FF); // south wall
		else
			return (0xDB592AFF); // north wall
			// return (0xF5F5F5FF); // north wall
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

unsigned int	get_pixel(mlx_texture_t	*t, int32_t pxposx, int32_t pxposy)
{
	int	r;
	int	g;
	int	b;

	r = t->pixels[(pxposy * t->width + pxposx) * t->bytes_per_pixel];
	g = t->pixels[(pxposy* t->width + pxposx) * t->bytes_per_pixel + 1];
	b = t->pixels[(pxposy * t->width + pxposx) * t->bytes_per_pixel + 2];
	return ((unsigned int)(r << 24 | g << 16 | b << 8 | 255));
}

void init_tex(t_game *game)
{
	game->draw->no_tex = mlx_load_png("./textures/stone_north.png");
	game->draw->so_tex = mlx_load_png("./textures/grass_south.png");
	game->draw->ea_tex =  mlx_load_png("./textures/brick_east.png");
	game->draw->we_tex = mlx_load_png("./textures/wood_west.png");
	// game->draw->no_img = mlx_texture_to_image(game->mlx, game->draw->no_tex);
	// mlx_delete_texture(game->draw->no_tex);
	// game->draw->so_img = mlx_texture_to_image(game->mlx, game->draw->so_tex);
	// mlx_delete_texture(game->draw->so_tex);
	// game->draw->we_img = mlx_texture_to_image(game->mlx, game->draw->we_tex);
	// mlx_delete_texture(game->draw->we_tex);
	// game->draw->ea_img = mlx_texture_to_image(game->mlx, game->draw->ea_tex);
	// mlx_delete_texture(game->draw->ea_tex);
}


// mlx_texture_t *pick_texture(t_game *game, int flag)
// {
// 	game->ray->agl = nor_angle(game->ray->agl); // normalize the angle
// 	if (flag == 0)
// 	{
// 		if (game->ray->agl > G_90 && game->ray->agl < G_270)
// 		{
// 			return (game->draw->we_tex); // west wall
// 		}
// 		else
// 		{
// 			return (game->draw->ea_tex); // east wall
// 		}
// 	}
// 	else
// 	{
// 		if (game->ray->agl > 0 && game->ray->agl < G_180)
// 		{
// 			return (game->draw->so_tex);// south wall
// 		}
// 		else
// 		{
// 			return (game->draw->no_tex); // north wall
// 		}
// 	}
// }

void	draw_wall (t_game *game, int ray, int top_px, int bottom_px)
{
	// vai ser as texturas e nao cor
	int	color;

	color = get_color(game, game->ray->wall);
	while (top_px < bottom_px) // change to go until reach the WIDTH
	{
		if (ray < 0) // check the x position
			return ;
		else if (ray >= WIDTH)
			return ;
		if (top_px < 0) // check the y position
			return ;
		else if (top_px >= WIDTH)
			return ;
		mlx_put_pixel(game->img, ray, top_px, color);
		top_px++;
	}
}

// void	draw_wall(t_game *game, int ray, int top_px, int bottom_px)
// {
// 	mlx_texture_t	*texture;
// 	// double			pxposx;
// 	// double			pxposy;
// 	// double			scale;
// 	// double			tex_pos;
	
// 	texture = pick_texture(game, game->ray->wall);
// 	// pxposx = (int)
// 	// tex_pos = 
// 	while (top_px < bottom_px)
// 	{
// 		// if (ray < 0) // check the x position
// 		// 	return ;
// 		// else if (ray >= WIDTH)
// 		// 	return ;
// 		// if (top_px < 0) // check the y position
// 		// 	return ;
// 		// else if (top_px >= WIDTH)
// 		// 	return ;
// 		// mlx_put_pixel(game->img, ray, top_px, get_pixel(texture, ray, bottom_px)); // crazy nice thing
// 		mlx_put_pixel(game->img, ray, top_px, get_pixel(texture, ray, top_px));
		
// 		top_px++;
// 	}
// }




// mlx_texture_t *pick_texture(t_game *game, int flag)
// {
// 	game->ray->agl = nor_angle(game->ray->agl);
// 	if (flag == 0)
// 	{
// 		if (game->ray->agl > G_90 && game->ray->agl < G_270)
// 		{
// 			return (game->draw->we_tex);
// 		}
// 			// return (0xC7CC29FF); // west wall
// 		else
// 		{
// 			return (game->draw->ea_tex);
// 		}
// 			// return (0xB5B5B5FF); // east wall
// 	}
// 	else
// 	{
// 		if (game->ray->agl > 0 && game->ray->agl < G_180)
// 		{
// 			return (game->draw->so_tex);
// 		}
// 			// return (0x4634EBFF); // south wall
// 		else
// 		{
// 			return (game->draw->no_tex);
// 		}
// 			// return (0xDB592AFF); // north wall
// 	}
// }

// int	reverse_bytes(int c)
// {
// 	unsigned int	b;

// 	b = 0;
// 	b |= (c & 0xFF) << 24;
// 	b |= (c & 0xFF00) << 8;
// 	b |= (c & 0xFF0000) >> 8;
// 	b |= (c & 0xFF000000) >> 24;
// 	return (b);
// }

// void	my_mlx_pixel_put(t_game *mlx, int x, int y, int color)
// {
// 	if (x < 0)
// 		return ;
// 	else if (x >= WIDTH)
// 		return ;
// 	if (y < 0)
// 		return ;
// 	else if (y >= HEIGHT)
// 		return ;
// 	mlx_put_pixel(mlx->img, x, y, color);
// }

// double	get_x_o(mlx_texture_t *texture, t_game *mlx)
// {
// 	double	x_o;

// 	if (mlx->ray->wall == 1)
// 		x_o = (int)fmodf((mlx->ray->h_x* \
// 		(texture->width / cell_size)), texture->width);
// 	else
// 		x_o = (int)fmodf((mlx->ray->v_y * \
// 		(texture->width / cell_size)), texture->width);
// 	return (x_o);
// }

// void	draw_wall(t_game *mlx, int t_pix, int b_pix, double wall_h)
// {
// 	double			x_o;
// 	double			y_o;
// 	mlx_texture_t	*texture;
// 	uint32_t		*arr;
// 	double			factor;
// 	int				index;

// 	index = 0;
// 	texture = pick_texture(mlx, mlx->ray->wall);
// 	arr = (uint32_t *)texture->pixels;
// 	factor = (double)texture->height / wall_h;
// 	x_o = get_x_o(texture, mlx);
// 	y_o = (t_pix - (HEIGHT / 2) + (wall_h / 2)) * factor;
// 	if (y_o < 0)
// 		y_o = 0;
// 	while (t_pix < b_pix)
// 	{
// 		my_mlx_pixel_put(mlx, index, t_pix, reverse_bytes \
// 		(arr[(int)y_o * texture->width + (int)x_o]));
// 		y_o += factor;
// 		t_pix++;
// 	}
// }



void	put_on_screen(t_game *game, int ray)
{
	double	wall_height;
	double	bottom_px;
	double	top_px;

	// printf("esse eh o valor do chao %i \n\n", game->draw->floor); // pq o chao eh zero?
	// printf("esse eh o valor do teto %i \n\n", game->draw->ceil); // pq fica mudando conforme roda o programa?
	game->ray->dist *= cos(nor_angle(game->ray->agl - game->plyr->agl));
	wall_height = (cell_size / game->ray->dist)
		* ((WIDTH / 2) / tan(game->plyr->fov_rad / 2));
	bottom_px = (HEIGHT / 2) + (wall_height / 2);
	top_px = (HEIGHT / 2) - (wall_height / 2);
	if (bottom_px > HEIGHT)
		bottom_px = HEIGHT;
	if (top_px < 0)
		top_px = 0;
	draw_floor(game, ray, bottom_px);
	draw_wall(game, ray, top_px, bottom_px);
	draw_ceiling(game, ray, top_px);
}
