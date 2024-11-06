/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checkers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 17:48:13 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/06 17:21:45 by edribeir      ########   odam.nl         */
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

// void	find_player(t_file *valid_file)
// {
// 	int	x;
// 	int	y;

// 	y = 0;
// 	while (valid_file->mapa[y])
// 	{
// 		x = 0;
// 		while (valid_file->mapa[y][x])
// 		{
// 			if (ft_isspace(valid_file->mapa[y][x]) || ft_isdigit(valid_file->mapa[y][x]))
// 				x++;
// 			if (valid_file->mapa[y][x] == 'N')
// 			{
// 				valid_file->map->player_x = x;
// 				valid_file->map->player_y = y;
// 				x++;
// 			}
// 		}
// 		y++;
// 	}
// }
