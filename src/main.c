/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 12:03:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/12 18:16:56 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	game_loop(void *param)
{
	t_game	*game;

	game = param;
	directions_decisions(game, 0.0, 0.0);
	casting_rays(game);
}

static int	start_game(t_file *input)
{
	t_game	*game;

	game = init_game(input);
	if (!game)
		return (1);
	if (init_mlx(game, input) == 1)
		return (1);
	init_player(game);
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	mlx_loop_hook(game->mlx, &game_loop, game);
	mlx_key_hook(game->mlx, &controls, game);
	mlx_loop(game->mlx);
	mlx_delete_image(game->mlx, game->img);
	mlx_terminate(game->mlx);
	cleaner_file(input);
	cleaner_game(game);
	return (0);
}

int	main(int argc, char **argv)
{
	t_file	input;

	if (argc != 2)
	{
			printf("   Wrong Input\n");
		printf("Please add one file!\n");
		return (1);
	}
	if (is_file_extension_valid(argv[1]) == false)
		return (1);
	init_file_struct(&input);
	if (is_file_valid(argv[1], &input) == false)
		return (cleaner_file(&input), 1);
	if (start_game(&input) == 1)
		return (1);
	return (0);
}
