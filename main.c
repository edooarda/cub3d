/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 12:03:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/10 15:28:16 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_file valid_file;

	valid_file.c_color = NULL;
	valid_file.f_color = NULL;
	valid_file.file = NULL;
	valid_file.mapa = NULL;
	valid_file.NO = NULL;
	valid_file.SO = NULL;
	valid_file.WE = NULL;
	valid_file.EA = NULL;
	if (argc == 2)
	{
		file_validator(argv[1], valid_file);
	}
	else
	{
		printf("   Wrong Input\n");
		printf("Please add one file!\n");
		return (1);
	}
	printf("oq tem dentro do NO = %s\n", valid_file.NO);
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