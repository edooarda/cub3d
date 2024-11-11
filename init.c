/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/09 13:50:36 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/11 15:40:39 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static void	init_angle(t_game *game)
// {
// 	game->angle.m_pi = 3.14159265358979323846;
// 	game->angle.g_90 = game->angle.m_pi / 2;
// 	game->angle.g_180 = game->angle.m_pi;
// 	game->angle.g_270 = 3 * game->angle.m_pi / 2;
// 	game->angle.g_360 = 2 * game->angle.m_pi;
// }

t_game	*init_game(t_file *input)
{
	t_game	*game;

	game = malloc(sizeof(t_game));
	if (!game)
		return (error_message("malloc fail to init game"), NULL);
	// init_angle(game);
	game->map = input->map;
	if (!game->map)
		return (error_message("malloc fail to init map"), NULL);
	game->plyr = ft_calloc(1, sizeof(t_player));
	if (!game->plyr)
		return (error_message("malloc fail to init player"), NULL);
	game->ray = ft_calloc(1, sizeof(t_ray));
	if (!game->ray)
		return (error_message("malloc fail to init ray"), NULL);
	game->wall = ft_calloc(1, sizeof(t_wall));
	if (!game->wall)
		return (error_message("malloc fail to init wall"), NULL);
	game->draw = input->valid_tex;
	return (game);
}

int	init_mlx(t_game *data, t_file *input)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!data->mlx)
	{
		ft_putendl_fd("Error Init Window MLX42", 2);
		cleaner_file(input);
		return (1);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		ft_putendl_fd("Error Init Window MLX42", 2);
		cleaner_file(input);
		return (1);
	}
	return (0);
}

bool	init_tex_struct(t_file *input)
{
	input->valid_tex = malloc(sizeof(t_tex));
	if (input->valid_tex == NULL)
		return (error_message("Malloc allocation for Tex failure"), false);
	input->valid_tex->floor = 0;
	input->valid_tex->ceil = 0;
	input->valid_tex->ea_tex = NULL;
	input->valid_tex->no_tex = NULL;
	input->valid_tex->so_tex = NULL;
	input->valid_tex->we_tex = NULL;
	return (true);
}

void	init_file_struct(t_file *input)
{
	input->file = NULL;
	input->mapa = NULL;
	input->map_y_lines = 0;
	input->no = NULL;
	input->so = NULL;
	input->we = NULL;
	input->ea = NULL;
	input->f_color = NULL;
	input->c_color = NULL;
	input->valid_tex = NULL;
	input->map = NULL;
}
