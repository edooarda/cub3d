/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/30 15:15:32 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/31 12:42:41 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	clear_frame(t_game *game)
// {
// 	int			x;
// 	int			y;
// 	// uint32_t	color;

// 	// color = ft_pixel(0x00, 0x00, 0x00, 0x00);
// 	x = 0;
// 	y = 0;
// 	while (y < HEIGHT)
// 	{
// 		while (x < WIDTH)
// 		{
// 			mlx_put_pixel(game->img, x, y, 0x00);
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// }

void release_controls(mlx_key_data_t keydata, t_game *game)
{
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_RELEASE))
		game->player->left_right = 0;
	else if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_RELEASE))
		game->player->left_right = 0;
	else if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_RELEASE))
		game->player->up_down = 0;
	else if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_RELEASE))
		game->player->up_down = 0;
	else if (keydata.key == MLX_KEY_A && keydata.action == MLX_RELEASE)
		game->player->rotation = 0;
	else if (keydata.key == MLX_KEY_D && keydata.action == MLX_RELEASE)
		game->player->rotation = 0;
}

void	controls(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	
	game = param;
	// clear_frame(game);
	// (void)keydata;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE) == true)
	{
		ft_putendl_fd("	Goodbye 👋, See you later! 😉", 1);
		mlx_close_window(game->mlx);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) == true)
		game->player->left_right = LEFT;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT) == true)
		game->player->left_right = RIGHT;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_UP) == true)
		game->player->up_down = UP;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN) == true)
		game->player->up_down = DOWN;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_A) == true)
		game->player->rotation = LEFT;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_D) == true)
		game->player->rotation = RIGHT;
	release_controls(keydata, game);
}
