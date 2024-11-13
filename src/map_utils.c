/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   map_utils.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: jovieira <jovieira@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/11/13 11:06:33 by jovieira      #+#    #+#                 */
/*   Updated: 2024/11/13 11:06:45 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	is_valid_char(char *str)
{
	char	*valid;
	int		i;

	valid = "01NSEW\n ";
	i = -1;
	while (str[++i])
	{
		if (!ft_strchr(valid, str[i]))
			return (1);
	}
	return (0);
}

static void	move_line(t_file *file, char *temp, int i, int fd)
{
	while (i++ < file->map->start_y)
	{
		temp = get_next_line(fd);
		free(temp);
	}
}

static int	cycle_line(t_file *file, char *temp, int i, int fd)
{
	while (1)
	{
		temp = get_next_line(fd);
		if (!temp)
			return (false);
		if (is_valid_char(temp))
			return (error_message("Invalid character"), free(temp), false);
		file->map->map2d[i++] = ft_strtrim(temp, "\n");
		free(temp);
	}
	return (true);
}

bool	is_map_filled(char *argv, t_file *file)
{
	int		fd;
	int		i;
	char	*temp;

	i = 0;
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (error_message("Fail to open file"), false);
	temp = NULL;
	move_line(file, temp, i, fd);
	i = 0;
	file->map->map2d = ft_calloc(file->map->h_map + 1, sizeof(char *));
	if (!file->map->map2d)
		return (error_message("Fail to create map"), false);
	if (cycle_line(file, temp, i, fd))
		return (false);
	free(temp);
	return (true);
}
