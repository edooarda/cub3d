/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   controls.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/30 15:15:32 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/30 15:24:10 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	controls(mlx_key_data_t keydata, void *param)
{
	t_game	*game;
	
	game = param;
	(void)keydata;
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE) == true)
	{
		ft_putendl_fd("	Goodbye 👋, See you later! 😉", 1);
		mlx_close_window(game->mlx);
	}
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT) == true)
		game->player->left_right = LEFT;
}