/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   draw_walls.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/06 19:11:20 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/13 11:45:07 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

// M_PI/2 is 90 degrees
// M_PI is 180 degrees
// 3*M_PI/2 is 270 degrees
static mlx_texture_t	*pick_texture(t_game *game, int n_s_wall)
{
	game->ray->agl = nor_angle(game->ray->agl);
	if (n_s_wall == false)
	{
		if (game->ray->agl > M_PI / 2 && game->ray->agl < 3 * M_PI / 2)
			return (game->draw->we_tex);
		else
			return (game->draw->ea_tex);
	}
	else
	{
		if (game->ray->agl > 0 && game->ray->agl < M_PI)
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
		if (game->ray->slice < 0 || game->ray->slice >= WIDTH
			|| t_pix < 0 || t_pix >= HEIGHT)
			return (false);
		if (game->wall->y_orient >= game->wall->tex->height)
			game->wall->y_orient = game->wall->tex->height - 1;
		if (game->wall->x_orient >= game->wall->tex->width)
			game->wall->x_orient = game->wall->tex->width - 1;
		mlx_put_pixel(game->img, game->ray->slice, t_pix,
			get_pixel(game->wall->tex_px[(int)game->wall->y_orient
				* game->wall->tex->width + (int)game->wall->x_orient]));
		game->wall->y_orient += game->wall->factor;
		t_pix++;
	}
	return (true);
}

void	draw_wall(t_game *g, int t_pix, int b_pix)
{
	g->wall->tex = pick_texture(g, g->ray->n_s_wall);
	g->wall->tex_px = (uint32_t *)g->wall->tex->pixels;
	g->wall->factor = (double)g->wall->tex->height / g->wall->wall_h;
	if (g->ray->n_s_wall == true)
		g->wall->x_orient = (int)fmod((g->ray->h_x
					* (g->wall->tex->width / CELL_SIZE)), g->wall->tex->width);
	else
		g->wall->x_orient = (int)fmod((g->ray->v_y
					* (g->wall->tex->width / CELL_SIZE)), g->wall->tex->width);
	if ((g->ray->n_s_wall == true && g->ray->agl > 0 && g->ray->agl < M_PI)
		|| (g->ray->n_s_wall == false
			&& (g->ray->agl > M_PI / 2 && g->ray->agl < 3 * M_PI / 2)))
		g->wall->x_orient = g->wall->tex->width - g->wall->x_orient - 1;
	g->wall->y_orient = (t_pix - (HEIGHT / 2) + (g->wall->wall_h / 2))
		* g->wall->factor;
	if (g->wall->y_orient < 0)
		g->wall->y_orient = 0;
	if (drawing_wall(g, t_pix, b_pix) == false)
		return ;
}
