/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:31 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/22 17:17:29 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include "./Libft/libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>

# define WIDTH 1920
# define HEIGHT 1080
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

// typedef struct s_player //the player structure
// {
// 	int  plyr_x; // player x position in pixels
// 	int  plyr_y; // player y position in pixels
// 	double angle; // player angle
// 	float fov_rd; // field of view in radians
// 	int  rot; // rotation flag
// 	int  l_r; // left right flag
// 	int  u_d; // up down flag
// } t_player;

typedef struct s_map
{
	int		player_x;
	int		player_y;
	int		map_width;
	int		map_height; // same as map_y_lines;
	char	**map2d; // same as mapa in the sfile
}	t_map;

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
	t_map	*map;
}	t_file;

typedef struct s_ray
{
	double	ray_angle;
	double	distance_to_wall;
	int		flag_wall;
	t_map	data;
	
}	t_ray;

typedef struct s_mlx
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_ray		*ray;
	
}	t_mlx;

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
void	find_player(t_file *valid_file);

// Color Checkers
int		color_check(t_file *valid_file, char *word);

// Texture Checkers
bool	is_texture_valid(t_file *valid_file);

#endif