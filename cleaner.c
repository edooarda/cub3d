/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaner.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 14:43:52 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/06 19:21:55 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleaner_game(t_game *game)
{
	// if (game->draw)
	// {
		
	// 	mlx_delete_texture(game->draw->ea_tex);
	// 	mlx_delete_texture(game->draw->no_tex);
	// 	mlx_delete_texture(game->draw->we_tex);
	// 	mlx_delete_texture(game->draw->so_tex);
	// }
	if (game->wall != NULL)
		free(game->wall);
	if (game->plyr != NULL)
		free(game->plyr);
	if (game->ray != NULL)
		free(game->ray);
	// if (game->map != NULL)
	// 	free(game->map);
}

void	cleaner_file(t_file *valid_file)
{
	if (valid_file->no != NULL)
		free(valid_file->no);
	if (valid_file->so != NULL)
		free(valid_file->so);
	if (valid_file->ea != NULL)
		free(valid_file->ea);
	if (valid_file->we != NULL)
		free(valid_file->we);
	if (valid_file->f_color != NULL)
		free(valid_file->f_color);
	if (valid_file->c_color != NULL)
		free(valid_file->c_color);
	if (valid_file->mapa != NULL)
		free_split(valid_file->mapa);
	if (valid_file->file != NULL)
		free_split(valid_file->file);
	if (valid_file->mapa_copy != NULL)
		free_split(valid_file->mapa_copy);
	// if (valid_file->valid_tex->NO_tex)
	// 	free(valid_file->valid_tex->NO_tex);
	// if (valid_file->valid_tex->EA_tex)
	// 	free(valid_file->valid_tex->EA_tex);
	// if (valid_file->valid_tex->WE_tex)
	// 	free(valid_file->valid_tex->WE_tex);
	// if (valid_file->valid_tex->SO_tex)
	// 	free(valid_file->valid_tex->SO_tex);
	if (valid_file->valid_tex) // colocar os frees dessas alocacoes num free para essa estrutura
		free(valid_file->valid_tex);
	// if (valid_file->map)
	// 	free(valid_file->map);
}
