/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_checkers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/24 16:28:52 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_information(t_file *file, char **data)
{
	int	i;
	int	lines;

	i = 0;
	lines = 0;
	while (data[i])
	{
		if (ft_strncmp(data[i], "NO", 2) == 0 && file->no == NULL)
			file->no = ft_strdup(data[i]);
		else if (ft_strncmp(data[i], "WE", 2) == 0 && file->we == NULL)
			file->we = ft_strdup(data[i]);
		else if (ft_strncmp(data[i], "SO", 2) == 0 && file->so == NULL)
			file->so = ft_strdup(data[i]);
		else if (ft_strncmp(data[i], "EA", 2) == 0 && file->ea == NULL)
			file->ea = ft_strdup(data[i]);
		else if (ft_strncmp(data[i], "F", 1) == 0 && file->f_color == NULL)
			file->f_color = ft_strdup(data[i]);
		else if (ft_strncmp(data[i], "C", 1) == 0 && file->c_color == NULL)
			file->c_color = ft_strdup(data[i]);
		else
			file->map_y_lines++;
		i++;
	}
}

char	*read_file(char *file)
{
	char	*line_read;
	char	*current_line;
	char	*temp;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_message("There is a problem Open the File"), NULL);
	current_line = get_next_line(fd);
	if (current_line == NULL)
		return (error_message("There is a problem Reading the File"), NULL);
	temp = ft_calloc(1, sizeof(char));
	if (temp == NULL)
		return (error_message("Allocation Memory Problem"), NULL);
	while (current_line != NULL)
	{
		line_read = ft_strjoin(temp, current_line);
		if (line_read == NULL)
			return (free(temp), NULL);
		free(current_line);
		current_line = get_next_line(fd);
		free(temp);
		temp = line_read;
	}
	return (close(fd), line_read);
}

bool	is_file_extension_valid(char *argv)
{
	int	len;

	len = ft_strlen(argv);
	if (argv && ft_strncmp(&argv[len - 4], ".cub", 4) != 0)
	{
		write(2, "Wrong extension, please use file.cub\n", 37);
		return (false);
	}
	return (true);
}



bool	is_file_valid(char *argv, t_file *valid_file)
{
	char	*file;

	file = read_file(argv);
	if (file == NULL)
		return (error_message("Something wrong reading the file"), false);
	valid_file->file = ft_split(file, '\n');
	free(file);
	if (valid_file->file == NULL)
		return (error_message("Something is wrong with the file"), false);
	fill_information(valid_file, valid_file->file);
	if (is_texture_valid(valid_file) == false)
		return (error_message("Invalid Input"), false);
	// tex_assing(valid_file);
	if (color_check(valid_file, valid_file->c_color) == false
		|| color_check(valid_file, valid_file->f_color) == false)
		return (false);
	if (is_map_filled(valid_file) == false)
		return (false);
	find_player(valid_file);
	// printf("player x -- %i\nplayer y -- %i\nmax y -- %i\n", valid_file->map->player_x, valid_file->map->player_y, valid_file->map->max_y);
	if (!map_area(valid_file))
		return (false);
	return (true);
}

