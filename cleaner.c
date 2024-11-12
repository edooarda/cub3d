/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaner.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 14:43:52 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/12 17:35:48 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleaner_game(t_game *game)
{
	if (game->wall != NULL)
		free(game->wall);
	if (game->plyr != NULL)
		free(game->plyr);
	if (game->ray != NULL)
		free(game->ray);
	if (game != NULL)
		free(game);
}

void	cleaner_tex(t_tex *tex)
{
	if (tex->no_tex != NULL)
		mlx_delete_texture(tex->no_tex);
	if (tex->so_tex != NULL)
		mlx_delete_texture(tex->so_tex);
	if (tex->we_tex != NULL)
		mlx_delete_texture(tex->we_tex);
	if (tex->ea_tex != NULL)
		mlx_delete_texture(tex->ea_tex);
	if (tex != NULL)
		free(tex);
}

void	cleaner_map(t_file *input)
{
	if (input->map->map2d)
		free_split(input->map->map2d);
	if (input->map != NULL)
		free(input->map);
}

void	cleaner_file(t_file *input)
{
	if (input->no != NULL)
		free(input->no);
	if (input->so != NULL)
		free(input->so);
	if (input->ea != NULL)
		free(input->ea);
	if (input->we != NULL)
		free(input->we);
	if (input->f_color != NULL)
		free(input->f_color);
	if (input->c_color != NULL)
		free(input->c_color);
	if (input->mapa != NULL)
		free_split(input->mapa);
	if (input->valid_tex)
		cleaner_tex(input->valid_tex);
	if (input->map)
		cleaner_map(input);
}
