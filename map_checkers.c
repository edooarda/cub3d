/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checkers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 17:48:13 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/18 21:04:00 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// void	flood_map(int x, int y, t_file *valid_file)
// {
	
// }

static bool	allocation_memory_map(t_file *valid_file)
{
	valid_file->mapa = malloc((valid_file->map_y_lines + 1) * sizeof(char *));
	if (valid_file->mapa == NULL)
	{
		cleaner_file(*valid_file); // check
		ft_putendl_fd("Allocation problem for the map", 2);
		return (false);
	}
	valid_file->mapa_copy = malloc((valid_file->map_y_lines + 1) * sizeof(char *));
	if (valid_file->mapa_copy == NULL)
	{
		cleaner_file(*valid_file);
		ft_putendl_fd("Allocation problem for the map copy", 2); // fazer free do q esta antes
		return (false);
	}
	return(true);
}

bool	is_map_filled(t_file *valid_file)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (allocation_memory_map(valid_file) == false)
		return (false);
	while (valid_file->file[i])
	{
		if (valid_file->file[i][0] == '\t' || valid_file->file[i][0] == '1' || valid_file->file[i][0] == ' ')
		{
			valid_file->mapa[j] = ft_strdup(valid_file->file[i]);
			valid_file->mapa_copy[j] = ft_strdup(valid_file->file[i]);
			j++;
		}
		i++;
	}
	valid_file->mapa[j] = NULL;
	valid_file->mapa_copy[j] = NULL;
	return (true);
}

void	map_area(t_file *valid_file, int x, int y)
{
	if (!valid_file->mapa[y - 1][x] || valid_file->mapa[y - 1][x] == ' ')
		return (error_message("no walls"));
	if (!valid_file->mapa[y + 1][x] || valid_file->mapa[y + 1][x] == ' ')
		return (error_message("no walls"));
	if (!valid_file->mapa[y][x - 1] || valid_file->mapa[y][x - 1] == ' ')
		return (error_message("no walls"));
	if (!valid_file->mapa[y][x + 1] || valid_file->mapa[y][x + 1] == ' ')
		return (error_message("no walls"));
}

void	find_player(t_file *valid_file)
{
	int	x;
	int	y;

	y = 0;
	while (valid_file->mapa[y])
	{
		x = 0;
		while (valid_file->mapa[y][x])
		{
			if (ft_isspace(valid_file->mapa[y][x]) || ft_isdigit(valid_file->mapa[y][x]))
				x++;
			if (valid_file->mapa[y][x] == 'N')
			{
				valid_file->map->player_x = x;
				valid_file->map->player_y = y;
				x++;
			}
		}
		y++;
	}
	while (valid_file->mapa_copy)
		map_area(valid_file, valid_file->map->player_x, valid_file->map->player_y);
}

