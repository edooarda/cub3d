/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_checkers.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/16 18:03:13 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
	if (is_texture_valid(valid_file) == false)
		return ;
	color_check(valid_file, valid_file->c_color); // fazer check e free
	color_check(valid_file, valid_file->f_color); // fazer check e free
	// tex_assing(valid_file);
	printf("error\n");
	if (is_map_filled(valid_file) == false )
		return ; // fazer free

	// tornar esta funcao bool
}
