/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checkers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 17:48:13 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/21 13:43:52 by jovieira      ########   odam.nl         */
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

int	map_area(t_file *valid_file)
{
	int	x;
	int	y;

	y = 0;
	while (valid_file->mapa[y])
	{
		x = 0;
		printf("%c\n", valid_file->mapa[y][2]);
		while (valid_file->mapa[y][x])
		{
			// printf("%s\n", valid_file->mapa[y]);
			// if (ft_isdigit(valid_file->mapa[y][x]) || ft_isspace(valid_file->mapa[y][x]))
			// {
				// if ((valid_file->mapa[0][x] != '1' || valid_file->mapa[0][x] == ' ' )&& valid_file->mapa[0][ft_strlen(valid_file->mapa[0])])
				// 	return (error_message("Missing north walls"), 1);
				// if (valid_file->mapa[y][0] != '1' || valid_file->mapa[y][0] == ' ')
				// 	return (error_message("Missing west walls"), 1);
			// }
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

