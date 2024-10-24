/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checkers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 17:48:13 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/24 12:11:56 by jovieira      ########   odam.nl         */
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

	i = 0;
	j = 0;
	if (allocation_memory_map(file) == false)
		return (false);
	while (file->file[i])
	{
		while (ft_isalpha(file->file[i][0]))
			i++;
		if (ft_isdigit(file->file[i][0]) || ft_isspace(file->file[i][0]))
		{
			file->mapa[j] = ft_strdup(file->file[i]);
			file->mapa_copy[j] = ft_strdup(file->file[i]);
			j++;
		}
		i++;
	}
	file->mapa[j] = NULL;
	file->mapa_copy[j] = NULL;
	return (true);
}

int	map_area(t_file *valid_file)
{
	int	x;
	int	y;

	y = 0;
	while (valid_file->mapa[y])
	{
		x = 0;
		printf("%s\n", valid_file->mapa[0]);
		while (valid_file->mapa[y][x])
		{
	
			x++;
		}
		y++;
	}
	return (0);
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
	while (valid_file->mapa_copy[y])
	{
		x = 0;
		while (valid_file->mapa_copy[y][x])
		{
			if (ft_isspace(valid_file->mapa_copy[y][x]) || ft_isdigit(valid_file->mapa_copy[y][x]))
				x++;
			if (player_pos(valid_file->mapa_copy[y][x]))
			{
				i++;
				if (i != 1)
					return (false);
				valid_file->map->player_x = x;
				valid_file->map->player_y = y;
				valid_file->map->player_dir = player_pos(valid_file->mapa_copy[y][x]);
				x++;
			}
		}
		y++;
		if (!valid_file->mapa_copy[y])
			valid_file->map->max_y = y;
	}
	return (true);
}