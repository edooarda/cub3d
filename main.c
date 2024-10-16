/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 12:03:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/16 16:10:01 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_file	valid_file;

	valid_file.c_color = NULL;
	valid_file.f_color = NULL;
	valid_file.file = NULL;
	valid_file.mapa = NULL;
	valid_file.map_y_lines = 0;
	valid_file.mapa_copy = NULL;
	valid_file.NO = NULL;
	valid_file.SO = NULL;
	valid_file.WE = NULL;
	valid_file.EA = NULL;
	valid_file.valid_tex = malloc(sizeof(t_tex));
	valid_file.valid_tex->floor = 0;
	valid_file.valid_tex->ceil = 0;
	// valid_file.valid_tex->EA_tex = malloc(sizeof(mlx_texture_t));
	// valid_file.valid_tex->NO_tex = malloc(sizeof(mlx_texture_t));
	// valid_file.valid_tex->SO_tex = malloc(sizeof(mlx_texture_t));
	// valid_file.valid_tex->WE_tex = malloc(sizeof(mlx_texture_t));
	if (argc == 2)
	{
		file_validator(argv[1], &valid_file); // fazer bool para fazer free se algo der errado
	}
	else
	{
		printf("   Wrong Input\n");
		printf("Please add one file!\n");
		return (1);
	}
	cleaner_file(valid_file);
}

// criar varios invalid maps