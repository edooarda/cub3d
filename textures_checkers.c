/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures_checkers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 18:00:58 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/28 18:07:34 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	tex_check(mlx_texture_t *png, char *path)
// {
// 	png = mlx_load_png(path);
// 	if (!png)
// 		return (error_message("Texture not found"));
// }

// void	tex_assing(t_file *valid_file)
// {
// 	tex_check(valid_file->valid_tex->no_tex, valid_file->no);
// 	tex_check(valid_file->valid_tex->so_tex, valid_file->so);
// 	tex_check(valid_file->valid_tex->we_tex, valid_file->we);
// 	tex_check(valid_file->valid_tex->ea_tex, valid_file->ea);
// }

bool	is_texture_valid(t_file *valid_file)
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

