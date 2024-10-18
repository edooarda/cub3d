/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   textures_checkers.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 18:00:58 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/18 15:27:22 by jovieira      ########   odam.nl         */
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
	char *temp;

	if (valid_file->NO != NULL && valid_file->SO != NULL && valid_file->WE != NULL && valid_file->EA != NULL) // if (str)
	{
		if (valid_file->NO) // if (ft_strncmp(str, CC, 2))
		{
			temp = valid_file->NO; // str = ./blabla sem CC
			// printf("esse eh o temp --%s\n", ft_strchr(temp, ' '));
			// pode ser um espaco ou uma tab?
			// fazer o free to temp mas antes fazer o valid_file->NO perder as letras, substring?
		}
		// printf("bla!\n");
		return (true);
	}
	printf("hey!\n");
	return (false);
}

