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

// void	flood_map(int x, int y, t_file *valid_file)
// {

// }

static bool	allocation_memory_map(t_file *file)
{
	file->mapa = malloc((file->map_y_lines + 1) * sizeof(char *));
	if (file->mapa == NULL)
	{
		cleaner_file(file);
		ft_putendl_fd("Allocation problem for the map", 2);
		return (false);
	}
	return (true);
}
/*(file->file[i][0] == '\t' || file->file[i][0] == '1' || file->file[i][0] == ' ')*/
bool	is_map_filled(t_file *file)
{
	int	i;
	int	j;

	i = 6;
	j = 0;
	if (allocation_memory_map(file) == false)
		return (false);
	while (file->file[i])
	{
		file->mapa[j] = ft_strdup(file->file[i]);
		j++;
		i++;
	}
	file->mapa[j] = NULL;
	return (true);
}

// int	map_wall(char **map, int x, int y, char def)
// {
// 	// while (map[y][x] != def)
// 	// {
// 		if (map[y][x] != def && (map[y][x + 1] != ' ' || map[y][x + 1] != '1'))
// 		{
// 			printf("in--%c--%i--%i-\n", map[y][x - 1], y, x - 1);
// 			error_message("Map not surronded");
// 			return (1);
// 		}
// 		if (ft_strchr("1 ", map[y][x + 1]) == 0)
// 		{
// 			printf("-%c-\n", map[y][x+1]);
// 			error_message("Map not surronded");
// 			return (1);
// 		}
// 		// y--;
// 	// }
// 	map_wall(map, y - 1, x, '1');
// 	map_wall(map, y + 1, x, '1');
// 	map_wall(map, y, x - 1, '1');
// 	map_wall(map, y, x + 1, '1');
// 	return (0);
// }

// int	map_area(t_file *valid_file)
// {
// 	int	x;
// 	int	y;
// int	map_area(t_file *valid_file)
// {
// 	int	x;
// 	int	y;
	
// 	y = 1;
// 	x = 0;
// 	while (valid_file->mapa[0][x])
// 	{
// 		if (ft_strchr("\t1 ", valid_file->mapa[0][x]) == 0)
// 			return(error_message("no top walls"), 1);
// 		x++;
// 	}
// 	x = 0;
// 	while (ft_isspace(valid_file->mapa[y][x]))
// 	{
// 		x++;
// 	}
// 	while (valid_file->mapa[y])
// 	{
// 		int len;
// 		len = ft_strlen(valid_file->mapa[y]);
// 		if (!ft_isspace(valid_file->mapa[y][0]))
// 			x = 0;
// 		if (ft_strchr("1", valid_file->mapa[y][x]) == 0 \
// 		|| ft_strrchr("1", valid_file->mapa[y][len - 1]) == 0)
// 		{
// 			return(error_message("no side walls"), 1);
// 		}
// 		y++;
// 	}
// 	y -= 1;
// 	while (valid_file->mapa[y][x])
// 	{
// 		if (ft_strchr("\t1 ", valid_file->mapa[y][x]))
// 		{
// 			if (valid_file->mapa[y][x] == ' ')
// 			{
// 				printf("out-%c--%i--%i-\n", valid_file->mapa[y][x], y, x);
// 				if (map_wall(valid_file->mapa, x, y, '1') == 1)
// 					return (1);
// 			}
// 		}
// 		x++;
// 	}
// 	return (1);
// }

char	player_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (c);
	return (0);
}

// void	check_width_height(t_file *map, int start)
// {
// 	int		i;

// 	while (map)
// 	{
// 		i = 0;
// 		if (map->mapa[i] /*&& ft_isdigit(map->mapa[i])*/)
// 		{
// 			if (start == 0)
// 				start = map->map->max_y;
// 			while (map->mapa[i])
// 				i++;
// 		}
// 		if (i > map->map->max_x)
// 			map->map->max_x = i - 1;
// 		map->map->max_y++;
// 	}
// 	map->map->max_y -= start;
// }

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
	// if (!start_pos(arr[y][x]) && !is_door(arr[y][x]))
	// 	arr[y][x] = '.';
	// if ((arr[y][x]) == 'C')
	// 	arr[y][x] = 'c';
	// if ((arr[y][x]) == 'L')
	// 	arr[y][x] = 'l';
}

int	is_changed(char c)
{
	if (c == 'l')
		return (1);
	return (0);
}

void	flood_fill(t_map *map, char **mapa, int y, int x)
{
	if (x == 0 || x == map->w_map)
		return (error_message("No walls at north or south border"));
	if (y == 0 || y == map->h_map)
	{
		printf("-%i--%i-\n-%c-\n", y, map->h_map, mapa[y][x]);
		return (error_message(" y No walls at north or south border"));
	}
	valid_space(map, mapa, x, y);
	if (!is_changed(mapa[y - 1][x]))
		flood_fill(map, mapa, y - 1, x);
	if (!is_changed(mapa[y + 1][x]))
		flood_fill(map, mapa, y + 1, x);
	if (!is_changed(mapa[y][x - 1]))
		flood_fill(map, mapa, y, x - 1);
	if (!is_changed(mapa[y][x + 1]))
		flood_fill(map, mapa, y, x + 1);
	if (!is_changed(mapa[y - 1][x - 1]))
		flood_fill(map, mapa, y - 1, x - 1);
	if (!is_changed(mapa[y - 1][x + 1]))
		flood_fill(map, mapa, y - 1, x + 1);
	if (!is_changed(mapa[y + 1][x + 1]))
		flood_fill(map, mapa, y + 1, x + 1);
	if (!is_changed(mapa[y + 1][x - 1]))
		flood_fill(map, mapa, y, x + 1);
}

bool	find_player(t_file *valid_file)
{
	int	x;
	int	y;
	int	i;
	int	start;

	y = 0;
	i = 0;
	start = 0;
	while (valid_file->mapa[y])
	{
		x = 0;
		while (valid_file->mapa[y][x])
		{
			if (start == 0)
				start = valid_file->map->h_map;
			if (player_pos(valid_file->mapa[y][x]))
			{
				i++;
				if (i != 1)
					return (false);
				valid_file->map->p_x = x;
				valid_file->map->p_y = y;
				valid_file->map->facing_to = player_pos(valid_file->mapa[y][x]);
				x++;
			}
			x++;
		}
		if (x > valid_file->map->w_map)
			valid_file->map->w_map = x - 1;
		valid_file->map->h_map++;
		y++;
	}
	valid_file->map->h_map -= start;
	return (true);
}