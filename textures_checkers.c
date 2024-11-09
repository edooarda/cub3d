/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures_checkers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 18:00:58 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/09 13:51:39 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

mlx_texture_t	*tex_check(mlx_texture_t *png, char *path)
{
	png = mlx_load_png(path);
	if (!png)
		return (false);
	return (png);
}

bool	tex_assign(t_file *input)
{
	input->valid_tex->no_tex = tex_check(input->valid_tex->no_tex, input->no);
	if (!input->valid_tex->no_tex)
		return (error_message("Invalid North texture path"), false);
	input->valid_tex->so_tex = tex_check(input->valid_tex->so_tex, input->so);
	if (!input->valid_tex->so_tex)
		return (error_message("Invalid South texture path"), false);
	input->valid_tex->we_tex = tex_check(input->valid_tex->we_tex, input->we);
	if (!input->valid_tex->we_tex)
		return (error_message("Invalid West texture path"), false);
	input->valid_tex->ea_tex = tex_check(input->valid_tex->ea_tex, input->ea);
	if (!input->valid_tex->ea_tex)
		return (error_message("Invalid East texture path"), false);
	return (true);
}

bool	is_texture_valid(t_file *input)
{
	input->no = space_jumper(input->no);
	if (input->no == NULL)
		return (false);
	input->so = space_jumper(input->so);
	if (input->so == NULL)
		return (false);
	input->ea = space_jumper(input->ea);
	if (input->ea == NULL)
		return (false);
	input->we = space_jumper(input->we);
	if (input->we == NULL)
		return (false);
	if (init_tex_struct(input) == false)
		return (false);
	return (true);
}
