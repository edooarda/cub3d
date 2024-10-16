/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaner.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 14:43:52 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/16 16:07:36 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cleaner_file(t_file valid_file)
{
	if (valid_file.NO != NULL)
		free(valid_file.NO);
	if (valid_file.SO != NULL)
		free(valid_file.SO);
	if (valid_file.EA != NULL)
		free(valid_file.EA);
	if (valid_file.WE != NULL)
		free(valid_file.WE);
	if (valid_file.f_color != NULL)
		free(valid_file.f_color);
	if (valid_file.c_color != NULL)
		free(valid_file.c_color);
	if (valid_file.mapa != NULL)
		free_split(valid_file.mapa);
	if (valid_file.file != NULL)
		free_split(valid_file.file);
	if (valid_file.mapa_copy != NULL)
		free_split(valid_file.mapa_copy);
	// if (valid_file.valid_tex->NO_tex)
	// 	free(valid_file.valid_tex->NO_tex);
	// if (valid_file.valid_tex->EA_tex)
	// 	free(valid_file.valid_tex->EA_tex);
	// if (valid_file.valid_tex->WE_tex)
	// 	free(valid_file.valid_tex->WE_tex);
	// if (valid_file.valid_tex->SO_tex)
	// 	free(valid_file.valid_tex->SO_tex);
	if (valid_file.valid_tex)  // colocar os frees dessas alocacoes num free para essa estrutura
		free(valid_file.valid_tex);
}
