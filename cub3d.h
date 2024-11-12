/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cub3d.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:31 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/12 17:28:12 by jovieira      ########   odam.nl         */
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
# define CELL_SIZE 64 // textures png 64x64
# define M_PI 3.14159265358979323846 // matematical number

// Player Moves
# define HIT_BOX 5
# define ROTATION_SPEED 0.05
# define PLAYER_SPEED 5
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

typedef struct s_map
{
	char	**map2d;
	char	facing_to;
	int		start_y;
	int		p_x;
	int		p_y;
	int		w_map;
	int		h_map;
}	t_map;

// typedef struct s_angle
// {
// 	double	m_pi;
// 	double	g_90;
// 	double	g_180;
// 	double	g_270;
// 	double	g_360;
// }	t_angle;

typedef struct s_ray
{
	int		slice;
	double	agl;
	double	dist;
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
	bool	n_s_wall;
	double	hdis;
}	t_ray;

typedef struct s_game
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_ray		*ray;
	t_player	*plyr;
	t_map		*map;
	t_tex		*draw;
	t_wall		*wall;
	// t_angle		angle;
}	t_game;

typedef struct s_file
{
	char	**mapa;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f_color;
	char	*c_color;
	t_tex	*valid_tex;
	t_map	*map;
}	t_file;

// Utils
bool	is_file_valid(char *argv, t_file *valid_file);
void	cleaner_file(t_file *valid_file);
void	cleaner_game(t_game *game);
void	error_message(char *message);
void	free_split(char **array);
char	*space_jumper(char *str);
int		is_full(t_file *file);

// Checkers
bool	is_file_extension_valid(char *argv);

// Map
bool	is_map_filled(char *argv, t_file *valid_file);
bool	find_player(t_file *file);
char	player_pos(char c);
int		flood_fill(t_map *map, int r, int y, int x);
void	map_check(t_map *map);

// Color
int		color_check(t_file *valid_file, char *word);

// Texture
bool	is_texture_valid(t_file *valid_file);
bool	tex_assign(t_file *input);

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
int		init_mlx(t_game *data, t_file *input);
void	init_file_struct(t_file *input);
bool	init_tex_struct(t_file *input);
t_game	*init_game(t_file *input);

#endif