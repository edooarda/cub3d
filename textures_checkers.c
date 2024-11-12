/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures_checkers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 18:00:58 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/12 14:35:38 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	tex_assign(t_file *input)
{
	input->valid_tex->no_tex = mlx_load_png(input->no);
	if (!input->valid_tex->no_tex)
		return (error_message("Invalid North texture path"), false);
	input->valid_tex->so_tex = mlx_load_png(input->so);
	if (!input->valid_tex->so_tex)
		return (error_message("Invalid South texture path"), false);
	input->valid_tex->we_tex = mlx_load_png(input->we);
	if (!input->valid_tex->we_tex)
		return (error_message("Invalid West texture path"), false);
	input->valid_tex->ea_tex = mlx_load_png(input->ea);
	if (!input->valid_tex->ea_tex)
		return (error_message("Invalid East texture path"), false);
	return (true);
}

bool	is_texture_valid(t_file *input)
{
	if (input->no == NULL)
		return (false);
	if (input->so == NULL)
		return (false);
	if (input->ea == NULL)
		return (false);
	if (input->we == NULL)
		return (false);
	if (init_tex_struct(input) == false)
		return (false);
	return (true);
}
