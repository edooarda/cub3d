/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_checkers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/11/09 17:26:59 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_information(t_file *file, char *data)
{
	if (file->no == NULL && ft_strncmp(data, "NO ", 3) == 0 )// mudar <-
		file->no = space_jumper(data);
	else if (ft_strncmp(data, "WE ", 3) == 0 && file->we == NULL)
		file->we = space_jumper(data);
	else if (ft_strncmp(data, "SO ", 3) == 0 && file->so == NULL)
		file->so = space_jumper(data);
	else if (ft_strncmp(data, "EA ", 3) == 0 && file->ea == NULL)
		file->ea = space_jumper(data);
	else if (ft_strncmp(data, "F ", 2) == 0 && file->f_color == NULL)
		file->f_color = ft_strdup(data);
	else if (ft_strncmp(data, "C ", 2) == 0 && file->c_color == NULL)
		file->c_color = ft_strdup(data);
}

bool	is_map(char *input, int line_num, t_file *file)
{
	int	i;
	char *temp;
	
	i = 0;
	temp = ft_strtrim(input, "\n\t ");
	while (temp[i] && (ft_isdigit(temp[i]) || player_pos(temp[i])))
		i++;
	if (ft_strlen(temp) == 0 || (!ft_isdigit(temp[i])  && temp[i] != '\0'))
		return (free(temp), false);
	if (!file->map)
	{
		file->map = ft_calloc(1, sizeof(t_map));//malloc check
		file->map->start_y = line_num;
	}
	return (free(temp), true);
}

int	read_file(char *file, t_file *input)
{
	char	*current_line;
	char	*temp;
	int		line_num;
	int		fd;

	line_num = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (error_message("There is a problem Open the File"), -1);
	current_line = get_next_line(fd);
	if (current_line == NULL)
		return (error_message("There is a problem Reading the File"), -1);
	temp = ft_calloc(1, sizeof(char));
	if (temp == NULL)
		return (error_message("Allocation Memory Problem"), -1);
	while (current_line != NULL)
	{
		fill_information(input, current_line);
		is_map(current_line, line_num, input);
		free(current_line);
		line_num++;
		current_line = get_next_line(fd);
	}
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
	read_file(argv, input);
	if (is_texture_valid(input) == false)
		return (error_message("Invalid Input"), false);
	if (tex_assign(input) == false)
		return (false);
	if (color_check(input, input->c_color) == false
		|| color_check(input, input->f_color) == false)
		return (false);
	if (is_map_filled(argv, input) == false)
		return (false);
	find_player(input);
	// map_check(input->map);
	// int i;
	// i = 0;
	// while (input->map->map2d[i])
	// {
	// 	printf("%s\n", input->map->map2d[i]);
	// 	i++;
	// }
	flood_fill(input->map, input->map->map2d, input->map->p_y, input->map->p_x);
	// printf("-%i--%i-\n-%c-\n", input->map->p_y, input->map->p_x, input->mapa[input->map->p_y][input->map->p_x]);
	// printf("max y -- %i\nmax x -- %i\n", input->map->max_y, input->map->max_x);
	// if (!map_area(input))
	// 	return (false);
	// while(input->map->map2d[i])
	// {
	// 	printf("%s\n", input->map->map2d[i]);
	// 	i++;
	// }
	return (true);
}
