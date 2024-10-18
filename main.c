/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 12:03:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/18 17:19:20 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_file_struct(t_file *valid_file)
{
	valid_file->c_color = NULL;
	valid_file->f_color = NULL;
	valid_file->file = NULL;
	valid_file->mapa = NULL;
	valid_file->map_y_lines = 0;
	valid_file->mapa_copy = NULL;
	valid_file->no = NULL;
	valid_file->so = NULL;
	valid_file->we = NULL;
	valid_file->ea = NULL;
	valid_file->valid_tex = malloc(sizeof(t_tex));
	valid_file->valid_tex->floor = 0;
	valid_file->valid_tex->ceil = 0;
	// valid_file->valid_tex->EA_tex = malloc(sizeof(mlx_texture_t));
	// valid_file->valid_tex->NO_tex = malloc(sizeof(mlx_texture_t));
	// valid_file->valid_tex->SO_tex = malloc(sizeof(mlx_texture_t));
	// valid_file->valid_tex->WE_tex = malloc(sizeof(mlx_texture_t));
}

int	main(int argc, char **argv)
{
	t_file	valid_file;

	if (argc == 2)
	{
		if (is_file_extension_valid(argv[1]) == false)
			return (1);
		init_file_struct(&valid_file);
		if (is_file_valid(argv[1], &valid_file) == false)
		{
			cleaner_file(&valid_file);
			return (1);
		}
		printf("everything is ok!\n");
		cleaner_file(&valid_file);
	}
	else
	{
		printf("   Wrong Input\n");
		printf("Please add one file!\n");
		return (1);
	}
}

// criar varios invalid maps