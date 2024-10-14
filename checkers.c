/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/14 15:42:55 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	filling_map(t_file *valid_file, char **file, int lines)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	valid_file->mapa = malloc((lines + 1) * sizeof(char *));
	if (valid_file->mapa == NULL)
	{
		ft_putendl_fd("Allocation problem", 2);
		return ;
	}
	while (file[i])
	{
		if (file[i][0] == '\t' || file[i][0] == '1' || file[i][0] == ' ')
		{
			valid_file->mapa[j] = ft_strdup(file[i]);
			j++;
		}
		i++;
	}
	valid_file->mapa[j] = NULL;
	// return(map);
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
	int map_lines = 0;
	while (array[i])
	{
		if (ft_strncmp(array[i], "NO", 2) == 0)
			valid_file->NO = ft_strdup(array[i]);
		else if (ft_strncmp(array[i], "WE", 2) == 0)
			valid_file->WE = ft_strdup(array[i]);
		else if (ft_strncmp(array[i], "SO", 2) == 0)
			valid_file->SO = ft_strdup(array[i]);
		else if (ft_strncmp(array[i], "EA", 2) == 0)
			valid_file->EA = ft_strdup(array[i]);
		else if (ft_strncmp(array[i], "F", 1) == 0)
			valid_file->f_color = ft_strdup(array[i]);
		else if (ft_strncmp(array[i], "C", 1) == 0)
			valid_file->c_color = ft_strdup(array[i]);
		else if(array[i][0] == '\t' || array[i][0] == '1' || array[i][0] == ' ')
			map_lines++;
		i++;
	}
	printf("esse eh o j --%i--\n", map_lines);
	printf("%p\n", valid_file->mapa);
	filling_map(valid_file, array, map_lines);
	printf("%p\n", valid_file->mapa);
	printf("esse eh o valor --%s---\n", valid_file->NO);
	printf("oq tem dentro do WE = --%s--\n", valid_file->WE);
	printf("oq tem dentro do EA = --%s--\n", valid_file->EA);
	printf("C color = --%s--\n", valid_file->c_color);
	printf("F color = --%s--\n", valid_file->f_color);
	int k = 0;
	printf("%p\n", valid_file->mapa);
	while(valid_file->mapa[k])
	{
		printf("This is the map = --%s--\n", valid_file->mapa[k]);
		k++;
	}
	free_split(array);
}
