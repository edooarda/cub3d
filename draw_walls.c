/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_wall.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/06 19:11:20 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/06 19:18:34 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static mlx_texture_t	*pick_texture(t_game *game, int flag)
{
	game->ray->agl = nor_angle(game->ray->agl);
	if (flag == 0)
	{
		if (game->ray->agl > G_90 && game->ray->agl < G_270)
			return (game->draw->we_tex);
		else
			return (game->draw->ea_tex);
	}
	else
	{
		if (game->ray->agl > 0 && game->ray->agl < G_180)
			return (game->draw->so_tex);
		else
			return (game->draw->no_tex);
	}
}

static int	get_pixel(int c)
{
	unsigned int	b;

	b = 0;
	b |= (c & 0xFF) << 24;
	b |= (c & 0xFF00) << 8;
	b |= (c & 0xFF0000) >> 8;
	b |= (c & 0xFF000000) >> 24;
	return (b);
}

static bool	drawing_wall(t_game *game, int t_pix, int b_pix)
{
	while (t_pix < b_pix)
	{
		if (game->ray->slice < 0)
			return (false);
		else if (game->ray->slice >= WIDTH)
			return (false);
		if (t_pix < 0)
			return (false);
		else if (t_pix >= HEIGHT)
			return (false);
		mlx_put_pixel(game->img, game->ray->slice, t_pix, 
			get_pixel(game->wall->tex_px[(int)game->wall->y_orient 
				* game->wall->tex->width + (int)game->wall->x_orient]));
		game->wall->y_orient += game->wall->factor;
		t_pix++;
	}
	return (true);
}

void	draw_wall(t_game *game, int t_pix, int b_pix)
{
	game->wall->tex = pick_texture(game, game->ray->wall);
	game->wall->tex_px = (uint32_t *)game->wall->tex->pixels;
	game->wall->factor = (double)game->wall->tex->height / game->wall->wall_h;
	if (game->ray->wall == true)
		game->wall->x_orient = (int)fmod((game->ray->h_x
			* (game->wall->tex->width / cell_size)), game->wall->tex->width);
	else
		game->wall->x_orient = (int)fmod((game->ray->v_y 
			* (game->wall->tex->width / cell_size)), game->wall->tex->width);
	game->wall->y_orient = (t_pix - (HEIGHT / 2) + (game->wall->wall_h / 2)) 
		* game->wall->factor;
	if (game->wall->y_orient < 0)
		game->wall->y_orient = 0;
	if (drawing_wall(game, t_pix, b_pix) == false)
		return ;
}
