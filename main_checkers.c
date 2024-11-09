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

void	fill_information(t_file *file, char **data)
{
	int	i;

	i = 0;
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

int	strnewline(char *str)
{
	int i;
	
	i = 0;
	while (str[i] != '\n')
		i++;
	return (i);
}

void	map_copy(char *file)//temp
{
	// char **map;
	int	i = 1;
	int	j = 0;

	// while (file[i] && ((ft_isalpha(file[i]) && ft_isalpha(file[i + 1]) && file[i + 2] == ' ') || (ft_isalpha(file[i]) && file[i + 1] == ' ')))
	while (file[j])
	{
		if (file[i] != '1' || file[i] != '0')
			i += strnewline(file);
		else
			i++;
		j += i;
	}
		printf("-%c--%i-\n",file[j], j);
}


bool	is_file_valid(char *argv, t_file *input)
{
	char	*file;

	file = read_file(argv);
	if (file == NULL)
		return (error_message("Something wrong reading the file"), false);
	map_copy(file);//temp
	input->file = ft_split(file, '\n');
	free(file);
	if (input->file == NULL)
		return (error_message("Something is wrong with the file"), false);
	fill_information(input, input->file);
	if (is_texture_valid(input) == false)
		return (error_message("Invalid Input"), false);
	if (tex_assign(input) == false)
		return (false);
	if (color_check(input, input->c_color) == false
		|| color_check(input, input->f_color) == false)
		return (false);
	if (is_map_filled(input) == false)
		return (false);
	input->map = malloc(sizeof(t_map));
	input->map->p_x = 0;
	input->map->p_y = 0;
	input->map->h_map = 0;
	input->map->w_map = 0;
	find_player(input);
	// int i = 0;
	// printf("max y -- %i\nmax x -- %i\n", input->map->h_map, input->map->w_map);
	// flood_fill(input->map, input->mapa, input->map->player_y, input->map->player_x);
	// printf("-%i--%i-\n-%c-\n", input->map->p_y, input->map->p_x, input->mapa[input->map->p_y][input->map->p_x]);
	// printf("max y -- %i\nmax x -- %i\n", input->map->max_y, input->map->max_x);
	// if (!map_area(input))
	// 	return (false);
	input->map->map2d = input->mapa;
	// while(input->map->map2d[i])
	// {
	// 	printf("%s\n", input->map->map2d[i]);
	// 	i++;
	// }
	return (true);
}
