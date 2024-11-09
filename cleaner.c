/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaner.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 14:43:52 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/09 11:46:37 by edribeir      ########   odam.nl         */
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
	// if (game->map != NULL)
	// 	free(game->map);
}

void	cleaner_tex(t_tex *tex)
{
	// if (tex->no_tex != 0)
	// 	mlx_delete_texture(tex->no_tex);
	// 	// free(tex->no_tex);
	// if (tex->so_tex != 0)
	// 	free(tex->so_tex);
	// if (tex->we_tex != 0)
	// 	free(tex->we_tex);
	// if (tex->ea_tex != 0)
	// 	free(tex->ea_tex);
	// 	mlx_delete_texture(tex->no_tex);
	// 	mlx_delete_texture(tex->we_tex);
	// 	mlx_delete_texture(tex->so_tex);
	// 	mlx_delete_texture(tex->ea_tex);
	// }
	if (tex != NULL)
		free(tex);
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
	if (input->file != NULL)
		free_split(input->file);
	if (input->mapa_copy != NULL)
		free_split(input->mapa_copy);
	// if (input->valid_tex->NO_tex)
	// 	free(input->valid_tex->NO_tex);
	// if (input->valid_tex->EA_tex)
	// 	free(input->valid_tex->EA_tex);
	// if (input->valid_tex->WE_tex)
	// 	free(input->valid_tex->WE_tex);
	// if (input->valid_tex->SO_tex)
	// 	free(input->valid_tex->SO_tex);
	// if (input->valid_tex) // colocar os frees dessas alocacoes num free para essa estrutura
	// 	free(input->valid_tex);
	cleaner_tex(input->valid_tex);
	// if (input->map)
	// 	free(input->map);
}
