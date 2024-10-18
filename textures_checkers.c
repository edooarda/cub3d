/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures_checkers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 18:00:58 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/18 17:44:40 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	tex_check(mlx_texture_t *png, char *path, char *msg)
// {
// 	png = mlx_load_png(path);
// 	if (!png)
// 		return (error_message(msg));
// }

// void	tex_assing(t_file *valid_file)
// {
// 	tex_check(valid_file->valid_tex->NO_tex, valid_file->NO, ERROR_TEX);
// 	tex_check(valid_file->valid_tex->SO_tex, valid_file->SO, ERROR_TEX);
// 	tex_check(valid_file->valid_tex->WE_tex, valid_file->WE, ERROR_TEX);
// 	tex_check(valid_file->valid_tex->EA_tex, valid_file->EA, ERROR_TEX);
// }

bool	is_texture_valid(t_file *valid_file) // is_texture_valid(char *str, char *CC)
{
	valid_file->no = space_jumper(valid_file->no);
	if (valid_file->no == NULL)
		return (false);
	valid_file->so = space_jumper(valid_file->so);
	if (valid_file->so == NULL)
		return (false);
	valid_file->ea = space_jumper(valid_file->ea);
	if (valid_file->ea == NULL)
		return (false);
	valid_file->we = space_jumper(valid_file->we);
	if (valid_file->we == NULL)
		return (false);
	return (true);
}

