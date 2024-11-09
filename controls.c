/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/30 15:15:32 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/09 10:41:41 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	release_controls(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_A && (keydata.action == MLX_RELEASE))
		game->plyr->left_right = 0;
	else if (keydata.key == MLX_KEY_D && (keydata.action == MLX_RELEASE))
		game->plyr->left_right = 0;
	else if (keydata.key == MLX_KEY_W && (keydata.action == MLX_RELEASE))
		game->plyr->up_down = 0;
	else if (keydata.key == MLX_KEY_S && (keydata.action == MLX_RELEASE))
		game->plyr->up_down = 0;
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_RELEASE)
		game->plyr->rot = 0;
	else if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_RELEASE)
		game->plyr->rot = 0;
}

void	controls(mlx_key_data_t keydata, void *param)
{
	t_game	*game;

	game = param;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE) == true)
	{
		ft_putendl_fd("	Goodbye 👋, See you later! 😉", 1);
		mlx_close_window(game->mlx);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A) == true)
		game->plyr->left_right = LEFT;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D) == true)
		game->plyr->left_right = RIGHT;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_W) == true)
		game->plyr->up_down = UP;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_S) == true)
		game->plyr->up_down = DOWN;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) == true)
		game->plyr->rot = LEFT;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) == true)
		game->plyr->rot = RIGHT;
	release_controls(keydata, game);
}
