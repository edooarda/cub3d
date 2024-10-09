/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/09 18:36:55 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool	file_checker(char *file)
{
	int	i;

	i = 0;
	while (file[i] != '\0')
	{
		if (file[i] == '\n' && file[i + 1] == '\n')
		{
			// pode ser usado o i, e conferir o file ate a posicao i encontrada, ou a partir da posicao i encontrada
			// conferir as cores e depois se for '\n' no inicio da str, pular todos para chegar no mapa
			printf("i am here\n"); // first time colors second print chegou no map
			// return (true);
		}
		i++;
	}
	return (false);
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

void	file_validator(char *argv)
{
	char *cpy_file;

	if (file_extension_checker(&argv[1]) == false)
		exit(EXIT_FAILURE);
	cpy_file = read_file(argv);
	if (cpy_file == NULL)
		error_message("Something wrong reading the file");
	printf("%s---\n", cpy_file);
	file_checker(cpy_file);
	// array = ft_split(test, '\n');
	// int i = 0;
	// while (array[i] != NULL)
	// {
	// 	printf("%s---\n", array[i]);
	// 	i++;
	// }
}


// void	file_check(char *str)
// {
// 	int fd;
// 	int i;

// 	i = 0;
// 	fd = open(str, O_RDONLY);
// 	while(i < 23)
// 	{
// 		printf("%s\n", get_next_line(fd));
// 		i++;
// 	}
// }

// static char	*gnl(int file, char *layout)
// {
// 	char	*temp_map;

// 	while (1)
// 	{
// 		temp_map = get_next_line(file);
// 		if (temp_map == NULL)
// 			break ;
// 		layout = ft_strjoin(layout, temp_map);
// 		if (layout == NULL)
// 			printf("bah\n");
// 			// msg("Error\nMalloc fail\n");
// 		free(temp_map);
// 	}
// 	close(file);
// 	free(temp_map);
// 	return (layout);
// }

// char	**map_copy(char *argv)
// {
// 	char	*layout;
// 	char	**full_map;
// 	int		file;

// 	layout = ft_strdup("");
// 	file = open(argv, O_RDONLY);
// 	if (file == -1)
// 		printf("bah\n");
// 		// msg("Error\nMalloc fail\n");
// 	layout = gnl(file, layout);
// 	full_map = ft_split(layout, '\n');
// 	free(layout);
// 	if (!full_map)
// 		printf("bah\n");
// 		// msg("Error\nMalloc fail\n");
// 	if (*full_map == NULL)
// 	{
// 		free(full_map);
// 		printf("bah\n");
// 		// msg("Error\nMalloc fail\n");
// 	}
// 	return (full_map);
// }

// char	**map_copy(char **argv)
// {
// 	int	i;
// 	int	x;
// 	int	y;

// 	x = 0;
// 	y = 0;
// 	argv = (char **)ft_calloc(sizeof(char *), (y + 1));
// 	if (!argv)
// 		printf("Malloc map\n");
// 	i = 0;
// 	while (i < y)
// 	{
// 		argv[i] = ft_calloc(sizeof(char), (x + 2));
// 		if (!argv[i])
// 			printf("Malloc map[y]\n");
// 		i++;
// 	}
// 	argv[i] = NULL;
// 	return (argv);
// }