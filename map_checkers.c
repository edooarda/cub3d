/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checkers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 17:48:13 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/31 14:18:03 by jovieira      ########   odam.nl         */
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
	file->mapa_copy = malloc((file->map_y_lines + 1) * sizeof(char *));
	if (file->mapa_copy == NULL)
	{
		cleaner_file(file);
		ft_putendl_fd("Allocation problem for the map copy", 2);
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
		file->mapa_copy[j] = ft_strdup(file->file[i]);
		j++;
		i++;
	}
	file->mapa[j] = NULL;
	file->mapa_copy[j] = NULL;
	return (true);
}

int	map_wall(char **map, int x, int y, char def)
{
	// while (map[y][x] != def)
	// {
		if (map[y][x] != def && (map[y][x + 1] != ' ' || map[y][x + 1] != '1'))
		{
			printf("in--%c--%i--%i-\n", map[y][x - 1], y, x - 1);
			error_message("Map not surronded");
			return (1);
		}
		if (ft_strchr("1 ", map[y][x + 1]) == 0)
		{
			printf("-%c-\n", map[y][x+1]);
			error_message("Map not surronded");
			return (1);
		}
		// y--;
	// }
	map_wall(map, y - 1, x, '1');
	map_wall(map, y + 1, x, '1');
	map_wall(map, y, x - 1, '1');
	map_wall(map, y, x + 1, '1');
	return (0);
}

int	map_area(t_file *valid_file)
{
	int	x;
	int	y;
	
	y = 1;
	x = 0;
	while (valid_file->mapa[0][x])
	{
		if (ft_strchr("\t1 ", valid_file->mapa[0][x]) == 0)
			return(error_message("no top walls"), 1);
		x++;
	}
	x = 0;
	while (ft_isspace(valid_file->mapa[y][x]))
	{
		x++;
	}
	while (valid_file->mapa[y])
	{
		int len;
		len = ft_strlen(valid_file->mapa[y]);
		if (!ft_isspace(valid_file->mapa[y][0]))
			x = 0;
		if (ft_strchr("1", valid_file->mapa[y][x]) == 0 \
		|| ft_strrchr("1", valid_file->mapa[y][len - 1]) == 0)
		{
			return(error_message("no side walls"), 1);
		}
		y++;
	}
	y -= 1;
	while (valid_file->mapa[y][x])
	{
		if (ft_strchr("\t1 ", valid_file->mapa[y][x]))
		{
			if (valid_file->mapa[y][x] == ' ')
			{
				printf("out-%c--%i--%i-\n", valid_file->mapa[y][x], y, x);
				if (map_wall(valid_file->mapa, x, y, '1') == 1)
					return (1);
			}
		}
		x++;
	}
	return (1);
}

char	player_pos(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (c);
	return (0);
	
}

bool	find_player(t_file *valid_file)
{
	int	x;
	int	y;
	int	i;

	y = 0;
	i = 0;
	while (valid_file->mapa[y])
	{
		x = 0;
		while (valid_file->mapa[y][x])
		{
			if (player_pos(valid_file->mapa[y][x]))
			{
				i++;
				if (i != 1)
					return (false);
				valid_file->map->player_x = x;
				valid_file->map->player_y = y;
				valid_file->map->player_dir = player_pos(valid_file->mapa[y][x]);
				x++;
			}
			x++;
		}
		y++;
		if (!valid_file->mapa[y])
			valid_file->map->max_y = y;
	}
	return (true);
}