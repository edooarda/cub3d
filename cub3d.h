/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:31 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/01 10:20:47 by edribeir      ########   odam.nl         */
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
# define cell_size 64 // textures png 64x64
# define M_PI 3.14159265358979323846 // matematical number
# define G_90 M_PI/2
# define G_180 M_PI
# define G_270  3*M_PI/2
# define G_360 2*M_PI

# define rotation_speed 0.01
# define player_speed 1
# define LEFT -1
# define RIGHT 1
# define UP 1
# define DOWN -1

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
	int		pos_x; // player x position in pixels
	int		pos_y; // player y position in pixels
	double	angle; // player angle
	float	fov_radians; // field of view in radians
	int		rotation; // rotation flag
	int		left_right; // left right flag
	int		up_down; // up down flag
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
	double	angle; // ray angle
	double	distance; // distance to the wall
	bool	wall;  // flag for the wall
	float	vert_x;
	float	vert_y;
	float	vert_x_step;
	float	vert_y_step;
	int		vert_pixel;
	float	vert_distance;
	float	horizon_x;
	float	horizon_y;
	float	horizon_x_step;
	float	horizon_y_step;
	int		horizon_pixel;
	float	horizon_distance;
} t_ray;

typedef struct s_data // temporario para entender funcionamento
{
	char **map2d; // the map
	int  p_x;  // player x position in the map
	int  p_y;  // player y position in the map
	int  w_map;  // map width
	int  h_map;  // map height
} t_temp;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_ray		*ray;
	t_player	*player;
	t_temp		*temp;
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
void	casting_rays(t_game *game);
float	translater_angle(float angle);
void	put_on_screen(t_game *game, int ray);

// Init
void	init_player(t_game *game);
t_temp *init_argumet();

// Player
void	directions_decisions(t_game *game, double move_x, double move_y);

// Controls
void	controls(mlx_key_data_t keydata, void *param);

#endif