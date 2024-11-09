/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures_checkers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 18:00:58 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/09 12:41:03 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	tex_check(mlx_texture_t *png, char *path)
{
	png = mlx_load_png(path);
	if (!png)
		return (false);
	return (true);
}

// bool	tex_assign(t_game *game, t_file *input)
// {
// 	if (tex_check(game->draw->no_tex, input->no) == false)
// 		return (error_message("North Texture not found"), false);
// 	if (tex_check(game->draw->so_tex, input->so) == false)
// 	{
// 		free(game->draw->no_tex);
// 		return (error_message("South Texture not found"), false);
// 	}
// 	if (tex_check(game->draw->we_tex, input->we) == false)
// 	{
// 		// free(game->draw->no_tex);
// 		// free(game->draw->so_tex);
// 		return (error_message("West Texture not found"), false);
// 	}
// 	if (tex_check(game->draw->ea_tex, input->ea) == false)
// 	{
// 		// free(game->draw->no_tex);
// 		// free(game->draw->so_tex);
// 		// free(game->draw->we_tex);
// 		return (error_message("East Texture not found") ,false);
// 	}
// 	return (true);
// }

// bool	tex_assign(t_file *input)
// {
// 	if (tex_check(input->valid_tex->no_tex, input->no) == false)
// 		return (error_message("North Texture not found"), false);
// 	if (tex_check(input->valid_tex->so_tex, input->so) == false)
// 	{
// 		// free(input->valid_tex->no_tex);
// 		return (error_message("South Texture not found"), false);
// 	}
// 	if (tex_check(input->valid_tex->we_tex, input->we) == false)
// 	{
// 		// free(input->valid_tex->no_tex);
// 		// free(input->valid_tex->so_tex);
// 		return (error_message("West Texture not found"), false);
// 	}
// 	if (tex_check(input->valid_tex->ea_tex, input->ea) == false)
// 	{
// 		// free(input->valid_tex->no_tex);
// 		// free(input->valid_tex->so_tex);
// 		// free(input->valid_tex->we_tex);
// 		return (error_message("East Texture not found") ,false);
// 	}
// 	return (true);
// }


bool	tex_assign(t_file *input)
{
	if (tex_check(input->valid_tex->no_tex, input->no) == false)
		return (error_message("North Texture not found"), false);
	if (tex_check(input->valid_tex->so_tex, input->so) == false)
	{
		// free(input->valid_tex->no_tex);
		return (error_message("South Texture not found"), false);
	}
	if (tex_check(input->valid_tex->we_tex, input->we) == false)
	{
		// free(input->valid_tex->no_tex);
		// free(input->valid_tex->so_tex);
		return (error_message("West Texture not found"), false);
	}
	if (tex_check(input->valid_tex->ea_tex, input->ea) == false)
	{
		// free(input->valid_tex->no_tex);
		// free(input->valid_tex->so_tex);
		// free(input->valid_tex->we_tex);
		return (error_message("East Texture not found") ,false);
	}
	return (true);
}

bool	init_tex_struct(t_file *input)
{
	input->valid_tex = ft_calloc(1 , sizeof(t_tex));
	if (input->valid_tex == NULL)
		return (error_message("Malloc allocation for Tex failure"), false);
	input->valid_tex->floor = 0;
	input->valid_tex->ceil = 0;
	// input->valid_tex->ea_tex = malloc(sizeof(mlx_texture_t));
	// input->valid_tex->no_tex = malloc(sizeof(mlx_texture_t));
	// input->valid_tex->so_tex = malloc(sizeof(mlx_texture_t));
	// input->valid_tex->we_tex = malloc(sizeof(mlx_texture_t));
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
