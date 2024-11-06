/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 12:03:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/06 18:19:18 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_mlx(t_game *data, t_file *input)
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
	// valid_file->map = malloc(sizeof(t_map));
	valid_file->valid_tex->floor = 0;
	valid_file->valid_tex->ceil = 0;
	// valid_file->valid_tex->ea_tex = malloc(sizeof(mlx_texture_t));
	// valid_file->valid_tex->no_tex = malloc(sizeof(mlx_texture_t));
	// valid_file->valid_tex->so_tex = malloc(sizeof(mlx_texture_t));
	// valid_file->valid_tex->we_tex = malloc(sizeof(mlx_texture_t));
}
void	game_loop(void *param)
{
	t_game	*game;

	game = param;
	directions_decisions(game, 0.0, 0.0);
	casting_rays(game);
}

int	start_game(t_file *input)
{
	t_game	game;

	game.map = init_argumet(); // will not be used in future // isso vira o map 
	game.plyr = calloc(1, sizeof(t_player)); // init function
	game.ray = calloc(1, sizeof(t_ray)); // init function
	game.wall = calloc(1, sizeof(t_wall)); // init function
	game.draw = input->valid_tex;
	if (init_mlx(&game, input) == 1)
		return (1);
	init_tex(&game);
	init_player(&game);
	mlx_image_to_window(game.mlx, game.img, 0, 0);
	mlx_loop_hook(game.mlx, &game_loop, &game);
	mlx_key_hook(game.mlx, &controls, &game);
	mlx_loop(game.mlx);
	mlx_delete_image(game.mlx, game.img);
	mlx_terminate(game.mlx);
	cleaner_file(input);
	cleaner_game(&game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_file	input;

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
		if (start_game(&input) == 1)
			return (1);
	}
	else
	{
		printf("   Wrong Input\n");
		printf("Please add one file!\n");
		return (1);
	}
}

t_map *init_argumet()// temporary fake values data
{
	t_map *dt = calloc(1, sizeof(t_map)); // init the data structure
	dt->map2d = calloc(10, sizeof(char *)); // init the map
	dt->map2d[0] = strdup("1111111111111111111111111"); //fill the map
	dt->map2d[1] = strdup("1000000000000000000100001");
	dt->map2d[2] = strdup("1001000000000P00000000001");
	dt->map2d[3] = strdup("1001000000000000001000001");
	dt->map2d[4] = strdup("1001000000000000001000001");
	dt->map2d[5] = strdup("1001000000100000001000001");
	dt->map2d[6] = strdup("1001000000000000001000001");
	dt->map2d[7] = strdup("1001000000001000001000001");
	dt->map2d[8] = strdup("1111111111111111111111111");
	dt->map2d[9] = NULL;
	dt->p_y = 3; // player y position in the map
	dt->p_x = 14; // player x position in the map
	dt->w_map = 25; // map width
	dt->h_map = 9; // map height
	dt->facing_to = 'N'; 
	return (dt); // return the data structure
}
