/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 12:03:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/14 14:40:03 by jovieira      ########   odam.nl         */
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
	valid_file.NO = NULL;
	valid_file.SO = NULL;
	valid_file.WE = NULL;
	valid_file.EA = NULL;
	valid_file.valid_tex = malloc(sizeof(t_tex));
	valid_file.valid_tex->EA_tex = malloc(sizeof(mlx_texture_t));
	valid_file.valid_tex->NO_tex = malloc(sizeof(mlx_texture_t));
	valid_file.valid_tex->SO_tex = NULL;
	valid_file.valid_tex->WE_tex = NULL;
	if (argc == 2)
	{
		file_validator(argv[1], &valid_file);
	}
	else
	{
		printf("   Wrong Input\n");
		printf("Please add one file!\n");
		return (1);
	}
	if (valid_file.NO != NULL)
		free(valid_file.NO);
	if (valid_file.SO != NULL)
		free(valid_file.SO);
	if (valid_file.EA != NULL)
		free(valid_file.EA);
	if (valid_file.WE != NULL)
		free(valid_file.WE);
	if (valid_file.file != NULL)
		free(valid_file.file);
}