/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_checkers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/12 18:25:35 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

bool	is_map(char *input, int line_num, t_file *file)
{
	int		i;
	char	*temp;

	i = 0;
	temp = ft_strtrim(input, "\n\t ");
	while (temp[i] && (ft_isdigit(temp[i]) || player_pos(temp[i])))
		i++;
	if (ft_strlen(temp) == 0 || (!ft_isdigit(temp[i]) && temp[i] != '\0'))
		return (free(temp), false);
	if (!file->map)
	{
		file->map = ft_calloc(1, sizeof(t_map));
		if (!file->map)
			return (error_message("Malloc fail"), false);
		file->map->start_y = line_num;
	}
	return (free(temp), true);
}

int	read_file(char *file, t_file *input)
{
	char	*current_line;
	int		line_num;
	int		fd;

	line_num = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_message("Fail to read file"), -1);
	current_line = get_next_line(fd);
	if (current_line == NULL)
		return (error_message("Fail to read file"), -1);
	while (current_line != NULL)
	{
		if (fill_information(input, current_line))
			return (free(current_line), -1);
		is_map(current_line, line_num, input);
		free(current_line);
		line_num++;
		current_line = get_next_line(fd);
	}
	free(current_line);
	if (input->map)
		input->map->h_map = line_num - input->map->start_y;
	return (close(fd));
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

bool	is_file_valid(char *argv, t_file *input)
{
	if (read_file(argv, input) == -1)
		return (false);
	if (is_texture_valid(input) == false)
		return (error_message("Invalid input"), false);
	if (tex_assign(input) == false)
		return (false);
	if (color_check(input, input->c_color) == false
		|| color_check(input, input->f_color) == false)
		return (false);
	if (is_full(input) == false)
		return (error_message("Missing elements"), false);
	if (is_map_filled(argv, input) == false)
		return (false);
	if (find_player(input) == false)
		return (error_message("Player not found"), false);
	if (flood_fill(input->map, 0, input->map->p_y, input->map->p_x))
		return (error_message("Invalid map"), false);
	return (true);
}
