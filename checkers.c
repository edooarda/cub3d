/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/15 10:44:23 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
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
			return (1);// add error
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

int	color_check(t_file *valid_file)
{
	int i;
	char	**color;
	char	**line;
	
	i = 0;
	valid_file->f_color[ft_strlen(valid_file->f_color)] = '\0';
	line = ft_split(valid_file->f_color, ' ');
	if (ft_arrlen(line) != 2)
		return (ft_free_arr(line), error_message("Wrong color selection"), 0);
	color = ft_split(valid_file->f_color, ',');
	if (ft_arrlen(color) != 3)
		return (ft_free_arr(color), error_message("Wrong color selection"), 0);
	if (get_colors(valid_file, color, line))
		return (EXIT_FAILURE);
	ft_free_arr(color);
	ft_free_arr(line);
	return (0);
}

char	*read_file(char *file)
{
	char	*line_read;
	char	*current_line;
	char	*temp;
	int		fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		error_message("There is a problem Open the File");
	current_line = get_next_line(fd);
	if (current_line == NULL)
		error_message("There is a problem Reading the File");
	temp = ft_calloc(1, sizeof(char));
	if (temp == NULL)
		error_message("Allocation Memory Problem");
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
	return (close (fd), line_read);
}

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

void	file_validator(char *argv, t_file *valid_file)
{
	char **array;
	if (file_extension_checker(&argv[1]) == false)
		exit(EXIT_FAILURE);
	valid_file->file = read_file(argv);
	if (valid_file->file == NULL)
		error_message("Something wrong reading the file");
	
	array = ft_split(valid_file->file, '\n');
	int i = 0;
	int j = 0;
	valid_file->mapa = malloc(sizeof(char*) * 256);
	while (array[i])
	{
		if (ft_strncmp(array[i], "NO", 2) == 0)
			valid_file->NO = array[i];
		else if (ft_strncmp(array[i], "WE", 2) == 0)
			valid_file->WE = array[i];
		else if (ft_strncmp(array[i], "SO", 2) == 0)
			valid_file->SO = array[i];
		else if (ft_strncmp(array[i], "EA", 2) == 0)
			valid_file->EA = array[i];
		else if (ft_strncmp(array[i], "F", 1) == 0)
			valid_file->f_color = array[i];
		else if (ft_strncmp(array[i], "C", 1) == 0)
			valid_file->c_color = array[i];
		else if(array[i][0] == '\t' || array[i][0] == '1' || array[i][0] == ' ')
		{
			valid_file->mapa[j] = ft_strdup(array[i]);
			j++;
		}
		// printf("esse eh o valor --%s---\n", array[i]);
		i++;
	}
	// tex_assing(valid_file);
	color_check(valid_file);
}
