/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:31 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/18 17:19:30 by edribeir      ########   odam.nl         */
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
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*ea_tex;
	mlx_texture_t	*we_tex;
	int32_t			ceil;
	int32_t			floor;
}	t_tex;

typedef struct s_file
{
	char	**file;
	char	**mapa;
	int		map_y_lines;
	char	**mapa_copy;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f_color;
	char	*c_color;
	t_tex	*valid_tex;
}	t_file;

// Utils
bool	is_file_valid(char *argv, t_file *valid_file);
void	cleaner_file(t_file *valid_file);
void	error_message(char *message);
void	free_split(char **array);
char	*space_jumper(char *str);

// Checkers
bool	is_file_extension_valid(char *argv);

// Map Checkers
bool	is_map_filled(t_file *valid_file);

// Color Checkers
int		color_check(t_file *valid_file, char *word);

// Texture Checkers
bool	is_texture_valid(t_file *valid_file);

#endif