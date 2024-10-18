/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_checkers.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/16 17:48:13 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/18 16:27:15 by edribeir      ########   odam.nl         */
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
		if (file->file[i][0] == '\t'
			|| file->file[i][0] == '1' || file->file[i][0] == ' ')
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
