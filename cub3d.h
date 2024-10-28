/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:31 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/28 18:09:14 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "MLX42/include/MLX42/MLX42.h"
# include <libft.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdbool.h>
# include <math.h>

# define WIDTH 1920
# define HEIGHT 1080

typedef struct s_tex
{
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*ea_tex;
	mlx_texture_t	*we_tex;
	int32_t			ceil;
	int32_t			floor;
}	t_tex;

typedef struct s_player
{
	int		pos_x;
	int		pos_y;
	double	direction_x;
	double	direction_y;
	double	angle_x;
	double	angle_y;
} t_player;

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
	int	map_x;
	int	map_y;
	int	step_x;
	int	step_y;
	int	side;
	int	wall;
	double	view_x;
	double	direction_x;
	double	direction_y;
	double	distance_x;
	double	distance_y;
	double	delta_distance_x;
	double	delta_distance_y;
	double	wall_distance;
	int		line_height;
	int		start_line;
	int		end_line;
}	t_ray;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_ray		ray;
	t_player	player;
}	t_game;

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

// Raycasting
void	init_ray(t_ray	*tmp);
void	game(void *param);

#endif