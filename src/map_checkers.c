/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checkers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 17:48:13 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/12 18:24:43 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	player_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (c);
	return (0);
}

int	flood_fill(t_map *map, int r, int y, int x)
{
	if (!map->map2d[y] || ft_strlen(map->map2d[y]) == 0)
		return (1);
	if (map->map2d[y][x] && (map->map2d[y][x] == '1' \
		|| map->map2d[y][x] == '2'))
		return (0);
	if ((y > map->h_map || y < 0)
		|| (x > (int)ft_strlen(map->map2d[y]) || x == 0))
		return (1);
	if (map->map2d[y][x] != '1'
		&& map->map2d[y][x] != '2' && map->map2d[y][x] != '0')
		return (1);
	map->map2d[y][x] = '2';
	r += flood_fill(map, r, y, x + 1);
	r += flood_fill(map, r, y, x - 1);
	r += flood_fill(map, r, y + 1, x);
	r += flood_fill(map, r, y - 1, x);
	return (r);
}

bool	tile_change(t_file *file, int y, int x, int i)
{
	if (player_pos(file->map->map2d[y][x]))
	{
		i++;
		if (i != 1)
			return (false);
		file->map->p_x = x;
		file->map->p_y = y;
		file->map->facing_to = player_pos(file->map->map2d[y][x]);
		file->map->map2d[y][x] = '0';
	}
	return (true);
}

bool	find_player(t_file *file)
{
	int	x;
	int	y;
	int	i;
	int	start;

	y = 0;
	i = 0;
	start = 0;
	while (file->map->map2d[++y])
	{
		x = 0;
		while (file->map->map2d[y][x])
		{
			if (start == 0)
				start = file->map->h_map;
			if (tile_change(file, y, x, i) == false)
				return (false);
			x++;
		}
		if (x > file->map->w_map)
			file->map->w_map = x - 1;
		file->map->h_map++;
	}
	file->map->h_map -= start;
	return (true);
}
