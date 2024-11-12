/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cleaner.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/14 14:43:52 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/12 18:17:09 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	tex_fill(t_file *file, char *data)
{
	if (ft_strncmp(data, "NO", 2) == 0)
	{
		if (file->no != NULL)
			return (error_message("Fail north"), 1);
		file->no = space_jumper(data);
	}
	if (ft_strncmp(data, "WE", 2) == 0)
	{
		if (file->we != NULL)
			return (error_message("Fail west"), 1);
		file->we = space_jumper(data);
	}
	else if (ft_strncmp(data, "SO", 2) == 0)
	{
		if (file->so != NULL)
			return (error_message("Fail south"), 1);
		file->so = space_jumper(data);
	}
	else if (ft_strncmp(data, "EA", 2) == 0)
	{
		if (file->ea != NULL)
			return (error_message("Fail east"), 1);
		file->ea = space_jumper(data);
	}
	return (0);
}

int	color_fill(t_file *file, char *data)
{
	if (ft_strncmp(data, "F", 1) == 0)
	{
		if (file->f_color != NULL)
			return (error_message("Fail floor color"), 1);
		file->f_color = ft_strdup(data);
	}
	else if (ft_strncmp(data, "C", 1) == 0)
	{
		if (file->c_color != NULL)
			return (error_message("Fail ceiling color"), 1);
		file->c_color = ft_strdup(data);
	}
	return (0);
}

int	fill_information(t_file *file, char *data)
{
	if (tex_fill(file, data))
		return (1);
	if (color_fill(file, data))
		return (1);
	return (0);
}
