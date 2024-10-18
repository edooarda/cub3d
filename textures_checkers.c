/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures_checkers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 18:00:58 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/18 15:36:17 by edribeir      ########   odam.nl         */
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

bool	is_texture_valid(t_file *valid_file)
{
	valid_file->NO = space_jumper(valid_file->NO);
	if (valid_file->NO == NULL)
		return (false);
	valid_file->SO = space_jumper(valid_file->SO);
	if (valid_file->SO == NULL)
		return (false);
	valid_file->EA = space_jumper(valid_file->EA);
	if (valid_file->EA == NULL)
		return (false);
	valid_file->WE = space_jumper(valid_file->WE);
	if (valid_file->WE == NULL)
		return (false);
	return (true);
}
