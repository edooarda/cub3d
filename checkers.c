/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/10 15:58:04 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	skip_char(char *line, char c)
{
	int i;

	i = 0;
	while (line[i] != c && line[i] != '\0')
		i++;
	return (i);
}

char	*textures_checker(char *line, int *i, char frst_l, char scnd_l)
{
	int j;
	int		len;
	char	*temp;

	len = 0;
	temp = NULL;
	// printf("line before strcmp %s\n", line);
	if (ft_strncmp(&line[(*i)], &frst_l, 1) == 0 && strncmp(&line[(*i) + 1], &scnd_l, 1) == 0)
	{
		j = skip_char(line, frst_l);
		// printf("entrei j = %i - %c\n", j, j);
		while (line[(*i)] != '\n')
		{
			len++;
			(*i)++;
		}
		printf("i = %i -- j = %i  ---- h = %i\n", (*i), j, len);
		temp = ft_substr(line, j, len);
	}
	printf("esse eh o TEMP %s\n", temp);
	return (temp);
}

// bool	textures_checker(t_file *file, int *i, char frst_l, char scnd_l)
// {
// 	int		j;
// 	int		len;
// 	char	*temp;

// 	len = 0;
// 	temp = NULL;
// 	if (ft_strncmp(&file->file[(*i)], &frst_l, 1) == 0 && strncmp(&file->file[(*i) + 1], &scnd_l, 1) == 0)
// 	{
// 		j = skip_char(file->file, frst_l);
// 		// printf("entrei j = %i - %c\n", j, j);
// 		while (file->file[(*i)] != '\n')
// 		{
// 			len++;
// 			(*i)++;
// 		}
// 		printf("i = %i -- j = %i  ---- h = %i\n", (*i), j, len);
// 		temp = ft_substr(file->file, j, len);
// 		if (temp[0] == 'N' && temp[1] == 'O')
// 		{
// 			file->NO = temp;
// 			printf("esse eh o q ta dentro da estrura %s\n", file->NO);
// 			return (true);
// 		}
// 		else if (frst_l == 'S' && scnd_l == 'O')
// 		{
// 			printf("humm?\n");
// 			file->SO = temp;
// 		}
// 		else if (frst_l == 'W' && scnd_l == 'E')
// 			file->WE = temp;
// 		else if (frst_l == 'E' && scnd_l == 'A')
// 			file->EA = temp;
// 	}
// 	printf("esse eh o TEMP %s\n", temp);
// }

bool	file_checker(t_file *valid_file)
{
	int	i;

	i = 0;
	while (valid_file->file[i])
	{
		// if (ft_strncmp(&valid_file->file[i], "N", 1) == 0 && strncmp(&valid_file->file[i + 1], "O", 1) == 0)
		// // if (valid_file->file[i] == 'N' && valid_file->file[i + 1] == '0')
		// {
		// 	// j = ft_strncmp(&valid_file->file[i], "N", 1);
		// 	printf("entrei\n");
		// 	while (valid_file->file[i] != '\n')
		// 		i++;
		// 	valid_file->NO = ft_substr(valid_file->file, j, i);
		// 	j = i;
		// 	printf("esse eh o NO %s\n", valid_file->NO);
		// }
		valid_file->NO = textures_checker(valid_file->file, &i, 'N', 'O');
		valid_file->SO = textures_checker(valid_file->file, &i, 'S', 'O');
		// valid_file->WE = textures_checker(valid_file->file, &i, 'W', 'E');
		valid_file->EA = textures_checker(valid_file->file, &i, 'E', 'A');
		printf(" this is i %i\n", i);
		printf("%s\n", valid_file->NO);
		printf("%s--\n", valid_file->SO);
		// printf("%s--\n", valid_file->WE);
		printf("%s--\n", valid_file->EA);
		if (valid_file->EA != NULL)
			break ;
		// if (valid_file->file[i] == '\n' && valid_file->file[i + 1] == '\n')
		// {
		// 	// pode ser usado o i, e conferir o file ate a posicao i encontrada, ou a partir da posicao i encontrada
		// 	// conferir as cores e depois se for '\n' no inicio da str, pular todos para chegar no mapa
		// 	printf("i am here %i\n", i);
		// 	break ; // first time colors second print chegou no map
		// 	// return (true);
		// }
		i++;
	}
	return (true);
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

void	file_validator(char *argv, t_file valid_file)
{
	if (file_extension_checker(&argv[1]) == false)
		exit(EXIT_FAILURE);
	valid_file.file = read_file(argv);
	if (valid_file.file == NULL)
		error_message("Something wrong reading the file");
	// printf("%s---\n", valid_file->file);
	file_checker(&valid_file);
	printf("oq tem dentro do WE = %s\n", valid_file.WE);
	// if (valid_file.NO != NULL)
	// 	free(valid_file.NO);
	// if (valid_file.SO != NULL)
	// 	free(valid_file.SO);
	// if (valid_file.EA != NULL)
	// 	free(valid_file.EA);
	// if (valid_file.WE != NULL)
	// 	free(valid_file.WE);
	if (valid_file.file != NULL)
		free(valid_file.file);
}
