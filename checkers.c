/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/16 16:06:06 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	allocation_memory_map(t_file *valid_file)
{
	valid_file->mapa = malloc((valid_file->map_y_lines + 1) * sizeof(char *));
	if (valid_file->mapa == NULL)
	{
		cleaner_file(*valid_file);
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

bool	filling_map(t_file *valid_file)
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

size_t	ft_arrlen(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
		return (0);
	while (arr[i])
		i++;
	return (i);
}

// void	tex_check(mlx_texture_t *png, char *path, char *msg)
// {
// 	png = mlx_load_png(path);
// 	if (!png)
// 		return (error_message(msg));
// }

// void	tex_assing(t_file *valid_file)
// {
// 	tex_check(valid_file->valid_tex->NO_tex, valid_file->NO, ERROR_TEX);
// 	tex_check(valid_file->valid_tex->SO_tex, valid_file->SO, ERROR_TEX);
// 	tex_check(valid_file->valid_tex->WE_tex, valid_file->WE, ERROR_TEX);
// 	tex_check(valid_file->valid_tex->EA_tex, valid_file->EA, ERROR_TEX);
// }

static int	get_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	get_colors(t_file *valid_file, char **color, char **word)
{
	int 	i;
	int		number;
	int		arg[3];
	int32_t	rgb;

	i = 0;
	while(color[i])
	{
		number = ft_atoi(color[i]);
		if (number < 0 || number > 255)
			return (error_message("Wrong color selection"), 1);
		arg[i] = number;
		i++;
	}
	rgb = get_rgb(arg[0], arg[1], arg[2], 255);
	if (!ft_strcmp(word[0], "F"))
		valid_file->valid_tex->floor = rgb;
	else if (!ft_strcmp(word[0], "C"))
		valid_file->valid_tex->ceil = rgb;
	return (EXIT_SUCCESS);
}

int	color_check(t_file *valid_file, char *word)
{
	int i;
	char	**color;
	char	**line;

	i = 0;
	word[ft_strlen(word)] = '\0';
	line = ft_split(word, ' ');
	if (ft_arrlen(line) != 2)
		return (free_split(line), error_message("Wrong color selection"), 0);
	color = ft_split(line[1], ',');
	if (ft_arrlen(color) != 3)
		return (free_split(color), error_message("Wrong color selection"), 0);
	if (!get_colors(valid_file, color, line))
		return (free_split(color), free_split(line), EXIT_FAILURE);
	free_split(color);
	free_split(line);
	return (EXIT_SUCCESS);
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

// void	flood_map(int x, int y, t_file *valid_file)
// {
	
// }



bool	file_extension_checker(char *argv)
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

void	fill_information(t_file *valid_file, char **data)
{
	int	i;
	int	lines;

	i = 0;
	lines = 0;
	while (data[i])
	{
		if (ft_strncmp(data[i], "NO", 2) == 0)
			valid_file->NO = ft_strdup(data[i]);
		else if (ft_strncmp(data[i], "WE", 2) == 0)
			valid_file->WE = ft_strdup(data[i]);
		else if (ft_strncmp(data[i], "SO", 2) == 0)
			valid_file->SO = ft_strdup(data[i]);
		else if (ft_strncmp(data[i], "EA", 2) == 0)
			valid_file->EA = ft_strdup(data[i]);
		else if (ft_strncmp(data[i], "F", 1) == 0)
			valid_file->f_color = ft_strdup(data[i]);
		else if (ft_strncmp(data[i], "C", 1) == 0)
			valid_file->c_color = ft_strdup(data[i]);
		else if(data[i][0] == '\t' || data[i][0] == '1' || data[i][0] == ' ')
			valid_file->map_y_lines++;
		i++;
	}
}

void	file_validator(char *argv, t_file *valid_file)
{
	char	*file;

	if (file_extension_checker(&argv[1]) == false)
		exit(EXIT_FAILURE);
	file = read_file(argv);
	if (file == NULL)
	{
		error_message("Something wrong reading the file");
		exit (EXIT_FAILURE);
	}
	valid_file->file = ft_split(file, '\n');
	free(file);
	if (valid_file->file == NULL)
	{
		error_message("Something is wrong with the file");
		exit (EXIT_FAILURE);
	}
	fill_information(valid_file, valid_file->file);
	printf("esse eh o tamanho do mapa %i\n", valid_file->map_y_lines);
	color_check(valid_file, valid_file->c_color); // fazer check e free
	color_check(valid_file, valid_file->f_color); // fazer check e free
	// tex_assing(valid_file);

	printf("error\n");
	if (filling_map(valid_file) == false )
		return ; // fazer free
}
