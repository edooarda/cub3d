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
	// int	j;
	// int	h;
	while (1)
	{
		// j = 0;
		temp = get_next_line(fd);
		if (!temp)
			break ;
		// while (temp[j])
		// {
		// 	printf("%i\n", j);
		// 	if (temp[j] == '\t')
		// 	{
		// 		h = 0;
		// 		while (h < 4)
		// 		{
		// 			printf("%s\n", temp);
		// 			temp[j] = ' ';
		// 			j++;
		// 			h++;
		// 		}
		// 		j += j;
		// 	}
		// 	j++;
		// }
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

void	valid_space(t_map *map, char **arr, int x, int y)
{
	if ((x == map->w_map - 1 || y == map->h_map - 1) && arr[y][x] != '1')
		return (error_message("No walls at border"));
	if (!arr[y - 1][x] || arr[y - 1][x] == ' ')
		return (error_message("No walls at N edge"));
	if (!arr[y + 1][x] || arr[y + 1][x] == ' ')
		return (error_message("No walls at S edge"));
	if (!arr[y][x - 1] || arr[y][x - 1] == ' ')
		return (error_message("No walls at W edge"));
	if (!arr[y][x + 1] || arr[y][x + 1] == ' ')
		return (error_message("No walls at E edge"));
	if (!arr[y - 1][x - 1] || arr[y - 1][x - 1] == ' ')
		return (error_message("No walls at NW edge"));
	if (!arr[y - 1][x + 1] || arr[y - 1][x + 1] == ' ')
		return (error_message("No walls at NE edge"));
	if (!arr[y + 1][x + 1] || arr[y + 1][x + 1] == ' ')
		return (error_message("No walls at SE edge"));
	if (!arr[y + 1][x - 1] || arr[y + 1][x - 1] == ' ')
		return (error_message("No walls at SW edge"));
}

// int	is_changed(char c)
// {
// 	if (c == 'l')
// 		return (1);
// 	return (0);
// }

void	flood_fill(t_map *map, char **mapa, int y, int x)
{
	if (x == 0 || x == map->w_map)
		return (error_message("No walls at north or south border"));
	if (y == 0 || y == map->h_map)
	{
		// printf("-%i--%i-\n-%c-\n", y, map->h_map, mapa[y][x]);
		return (error_message(" y No walls at north or south border"));
	}
	// valid_space(map, mapa, x, y);
	printf("y -- %i\n", map->p_y);
	// if (!is_changed(mapa[y - 1][x]))
		flood_fill(map, mapa, y - 1, x);
	// if (!is_changed(mapa[y + 1][x]))
		flood_fill(map, mapa, y + 1, x);
	// if (!is_changed(mapa[y][x - 1]))
		flood_fill(map, mapa, y, x - 1);
	// if (!is_changed(mapa[y][x + 1]))
		flood_fill(map, mapa, y, x + 1);
	// if (!is_changed(mapa[y - 1][x - 1]))
		flood_fill(map, mapa, y - 1, x - 1);
	// if (!is_changed(mapa[y - 1][x + 1]))
		flood_fill(map, mapa, y - 1, x + 1);
	// if (!is_changed(mapa[y + 1][x + 1]))
		flood_fill(map, mapa, y + 1, x + 1);
	// if (!is_changed(mapa[y + 1][x - 1]))
		flood_fill(map, mapa, y, x + 1);
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
				x++;
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