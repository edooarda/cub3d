/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:31 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/06 19:19:57 by edribeir      ########   odam.nl         */
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

// Angles
# define G_90 M_PI/2
# define G_180 M_PI
# define G_270  3*M_PI/2
# define G_360 2*M_PI

// Player Moves
# define rotation_speed 0.05
# define player_speed 5
# define LEFT -1
# define RIGHT 1
# define UP 1
# define DOWN -1

typedef struct s_wall
{
	double			wall_h;
	double			x_orient;
	double			y_orient;
	mlx_texture_t	*tex;
	uint32_t		*tex_px;
	double			factor;
}	t_wall;

typedef struct s_tex
{
	mlx_texture_t	*no_tex;
	mlx_texture_t	*so_tex;
	mlx_texture_t	*ea_tex;
	mlx_texture_t	*we_tex;
	uint32_t		ceil;
	uint32_t		floor;
}	t_tex;

typedef struct s_player
{
	int			pos_x;
	int			pos_y;
	double		agl;
	double		fov_rad;
	double		rot;
	int			left_right;
	int			up_down;
}	t_player;

// typedef struct s_map
// {
// 	int		player_x;
// 	int		player_y;
// 	int		map_width;
// 	int		map_height; // same as map_y_lines;
// 	char	**map2d; // same as mapa in the sfile
// }	t_map;

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
	// t_map	*map;
}	t_file;

typedef struct s_ray
{
	int		slice;
	double	agl;
	double	dist;
	bool	wall;
	double	v_x;
	double	v_y;
	double	v_x_step;
	double	v_y_step;
	int		v_px;
	double	vdis;
	double	h_x;
	double	h_y;
	double	h_x_step;
	double	h_y_step;
	int		h_px;
	double	hdis;
}	t_ray;

typedef struct s_data // temporario para entender funcionamento
{
	char **map2d; // the map
	int  p_x;  // player x position in the map
	int  p_y;  // player y position in the map
	char  facing_to;
	int  w_map;  // map width
	int  h_map;  // map height
} t_map;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_ray		*ray;
	t_player	*plyr;
	t_map		*map;
	t_tex		*draw;
	t_wall		*wall;
}	t_game;

// Utils
bool	is_file_valid(char *argv, t_file *valid_file);
void	cleaner_file(t_file *valid_file);
void	cleaner_game(t_game *game);
void	error_message(char *message);
void	free_split(char **array);
char	*space_jumper(char *str);

// Checkers
bool	is_file_extension_valid(char *argv);

// Map
bool	is_map_filled(t_file *valid_file);
void	find_player(t_file *valid_file);

// Color
int		color_check(t_file *valid_file, char *word);

// Texture
bool	is_texture_valid(t_file *valid_file);
void	init_tex(t_game *game);

// Raycasting
void	casting_rays(t_game *game);
double	nor_angle(double angle);
void	put_on_screen(t_game *game, int ray);

// Wall
void	draw_wall(t_game *game, int t_pix, int b_pix);

// Player
void	init_player(t_game *game);
void	directions_decisions(t_game *game, double move_x, double move_y);

// Controls
void	controls(mlx_key_data_t keydata, void *param);

// Init
t_map *init_argumet();

#endif