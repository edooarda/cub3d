/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:31 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/14 16:24:03 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "./Libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>

# define ERROR_TEX "Texture not found"

typedef struct s_tex
{
	mlx_texture_t *NO_tex;
	mlx_texture_t *SO_tex;
	mlx_texture_t *EA_tex;
	mlx_texture_t *WE_tex;
	int32_t			ceil;
	int32_t			floor;
}	t_tex;

typedef struct s_file
{
	char 	*file;
	char 	**mapa;
	char 	*NO;
	char 	*SO;
	char 	*WE;
	char 	*EA;
	char	*f_color;
	char 	*c_color;
	t_tex	*valid_tex;
}	t_file;



void	file_validator(char *argv, t_file *valid_file);
void	error_message(char *message);

#endif