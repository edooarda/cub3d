/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checkers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 17:48:13 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/09 17:32:12 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_valid_char(char *str)
{
	char *valid;
	int	i;

	valid = "01NSEW\n ";
	i = -1;
	while (str[++i])
	{
		if (!ft_strchr(valid, str[i]))
		{
			printf("%i\n", str[i]);
			return (1);
		}
	}
	return (0);
}

bool	is_map_filled(char *argv, t_file *file)
{
	int	fd;
	int	i;
	char	*temp;

	i = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (error_message("fudeu"), false);
	while (i++ < file->map->start_y)
	{
		temp = get_next_line(fd);
		free(temp);
	}
	i = 0;
	file->map->map2d = ft_calloc(file->map->h_map + 1, sizeof(char *));
	if (!file->map->map2d)
		return (error_message("fudeu mapa"), false);
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			break ;
		if (is_valid_char(temp))
			return (error_message("fudeu character"), false);
		file->map->map2d[i++] = ft_strtrim(temp, "\n");
		free(temp);
	}
	free(temp);
	return (true);
}

char	player_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (c);
	return (0);
}

int	flood_fill(t_map *map, int r, int y, int x)
{
	if (!map->map2d[y])
		return (1);
	if (map->map2d[y][x] && (map->map2d[y][x] == '1' \
		|| map->map2d[y][x] == '2'))
		return (0);
	if ((y > map->h_map || y < 0) || (x > (int)ft_strlen(map->map2d[y]) || x == 0))
		return (1);
	if (map->map2d[y][x] != '1' && map->map2d[y][x] != '2' && map->map2d[y][x] != '0')
		return (1);
	map->map2d[y][x] = '2';
	r += flood_fill(map, r, y, x + 1);
	r += flood_fill(map, r, y, x - 1);
	r += flood_fill(map, r, y + 1, x);
	r += flood_fill(map, r ,y - 1, x);
	return (r);
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
	while (file->map->map2d[y])
	{
		x = 0;
		while (file->map->map2d[y][x])
		{
			if (start == 0)
				start = file->map->h_map;
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
			x++;
		}
		if (x > file->map->w_map)
			file->map->w_map = x - 1;
		file->map->h_map++;
		y++;
	}
	file->map->h_map -= start;
	return (true);
}