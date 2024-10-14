/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/14 12:04:54 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// size_t	skip_char(char *line, char c)
// {
// 	int i;

// 	i = 0;
// 	while (line[i] != c && line[i] != '\0')
// 		i++;
// 	return (i);
// }

// char	*textures_checker(char *line, int *i, char *values)
// {
// 	int j;
// 	int		len;
// 	char	*temp;
	

// 	len = -3;
// 	temp = NULL;

// 	// printf("line before strcmp %c\n", line[(*i)]);
// 	if (ft_strncmp(&line[(*i)], values, 2) == 0)
// 	{
// 		// add check for tabs and jump a lot of tabs
// 		j = *i + 1 + skip_char(line, ' ');
// 		while (line[(*i)] != '\n')
// 		{
// 			len++;
// 			(*i)++;
// 		}
// 		// printf("i = %i -- j = %i  ---- h = %i\n", (*i), j, len);
// 		temp = ft_substr(line, j, len);
// 		printf("esse eh o TEMP %s--\n", temp);
// 	}
// 	// printf("entrei i = '%i' - '%c'\n", line[(*i)], line[(*i)]);
// 	(*i)++;
// 	return (temp);
// }

// bool	file_checker(t_file *valid_file)
// {
// 	int	i;

// 	i = 0;
// 	while (valid_file->file[i] && i < 4)
// 	{
// 		// if (ft_strncmp(&valid_file->file[i], "N", 1) == 0 && strncmp(&valid_file->file[i + 1], "O", 1) == 0)
// 		// // if (valid_file->file[i] == 'N' && valid_file->file[i + 1] == '0')
// 		// {
// 		// 	// j = ft_strncmp(&valid_file->file[i], "N", 1);
// 		// 	printf("entrei\n");
// 		// 	while (valid_file->file[i] != '\n')
// 		// 		i++;
// 		// 	valid_file->NO = ft_substr(valid_file->file, j, i);
// 		// 	j = i;
// 		// 	printf("esse eh o NO %s\n", valid_file->NO);
// 		// }
// 		// if (textures_checker(valid_file, &i, 'N', 'O') == false)
// 		// 	return (false);
// 		valid_file->NO = textures_checker(valid_file->file, &i, "NO");
// 		valid_file->SO = textures_checker(valid_file->file, &i, "SO");
// 		valid_file->WE = textures_checker(valid_file->file, &i, "WE");
// 		valid_file->EA = textures_checker(valid_file->file, &i, "EA");
// 		printf(" this is i %i\n", i);
// 		// printf("%s\n", valid_file->NO);
// 		// printf("%s--\n", valid_file->SO);
// 		// printf("%s--\n", valid_file->WE);
// 		// printf("%s--\n", valid_file->EA);
// 		// if (valid_file->EA != NULL)
// 		// 	break ;
// 		// if (valid_file->file[i] == '\n' && valid_file->file[i + 1] == '\n')
// 		// {
// 		// 	// pode ser usado o i, e conferir o file ate a posicao i encontrada, ou a partir da posicao i encontrada
// 		// 	// conferir as cores e depois se for '\n' no inicio da str, pular todos para chegar no mapa
// 		// 	printf("i am here %i\n", i);
// 		// 	break ; // first time colors second print chegou no map
// 		// 	// return (true);
// 		// }
// 		i++;
// 	}
// 	return (true);
// }

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
		else if(ft_strchr("\t1 ", array[i][0]) /*array[i][0] == '\t' || array[i][0] == '1' || array[i][0] == ' '*/)
		{
			valid_file->mapa[j] = ft_strdup(array[i]);
			j++;
		}
		// printf("esse eh o valor --%s---\n", array[i]);
		i++;
	}
	printf("esse eh o valor --%s---\n", valid_file->NO);
	printf("oq tem dentro do WE = --%s--\n", valid_file->WE);
	printf("oq tem dentro do EA = --%s--\n", valid_file->EA);
	printf("oq tem dentro do SO = --%s--\n", valid_file->SO);
	printf("F color = --%s--\n", valid_file->f_color);
	printf("C color = --%s--\n", valid_file->c_color);
	int k = 0;
	while(valid_file->mapa[k])
	{
		printf("C color = --%s--\n", valid_file->mapa[k]);
		k++;
	}
	// printf("%s---\n", valid_file->file);
	// file_checker(valid_file);
}
