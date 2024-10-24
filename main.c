/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 12:03:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/24 13:05:27 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	controls(mlx_key_data_t keydata, void *param)
{
	t_mlx	*data;
	
	data = param;
	(void)keydata;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE) == true)
	{
		ft_putendl_fd("	Goodbye 👋, See you later! 😉", 1);
		mlx_close_window(data->mlx);
	}
}


int	init_mlx(t_mlx *data, t_file *input)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "cub3D", false);
	if (!data->mlx)
	{
		ft_putendl_fd("Error Init Window MLX42", 2);
		cleaner_file(input);
		return (1);
	}
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (!data->img)
	{
		ft_putendl_fd("Error Init Window MLX42", 2);
		cleaner_file(input);
		return (1);
	}
	return (0);
}

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
	valid_file->map = malloc(sizeof(t_map));
	valid_file->valid_tex->floor = 0;
	valid_file->valid_tex->ceil = 0;
	// valid_file->valid_tex->EA_tex = malloc(sizeof(mlx_texture_t));
	// valid_file->valid_tex->NO_tex = malloc(sizeof(mlx_texture_t));
	// valid_file->valid_tex->SO_tex = malloc(sizeof(mlx_texture_t));
	// valid_file->valid_tex->WE_tex = malloc(sizeof(mlx_texture_t));
}

int	main(int argc, char **argv)
{
	t_file	input;
	t_mlx	data;

	if (argc == 2)
	{
		if (is_file_extension_valid(argv[1]) == false)
			return (1);
		init_file_struct(&input);
		if (is_file_valid(argv[1], &input) == false)
		{
			cleaner_file(&input);
			return (1);
		}
		if (init_mlx(&data, &input) == 1)
			return (1);
		// mlx_image_to_window(data.mlx, data.img, 0, 0);
		// mlx_key_hook(data.mlx, &controls, &data);
		// mlx_loop(data.mlx);
		// mlx_terminate(data.mlx);
		printf("everything is ok!\n");
		cleaner_file(&input);
	}
	else
	{
		printf("   Wrong Input\n");
		printf("Please add one file!\n");
		return (1);
	}
}
