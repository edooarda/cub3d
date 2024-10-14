/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   checkers.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 11:22:18 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/14 11:52:36 by jovieira      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// static bool	ft_isspace(char c)
// {
// 	return (c == '\t' || c == '\n' || c == '\v' || \
// 		c == '\f' || c == '\r' || c == ' ');
// }

size_t	skip_char(char *line, char c)
{
	int i;

	i = 0;
	while (line[i] != c && line[i] != '\0')
		i++;
	return (i);
}

char	*textures_checker(char *line, int *i, char *values)
{
	int j;
	int		len;
	char	*temp;
	

	len = -3;
	temp = NULL;

	if (ft_strncmp(&line[(*i)], values, 2) == 0)
	{
		// printf("%c\n", line[(*i)]);
		// while (ft_isspace(line[(*i)]))
		// 	line[(*i)]++;
		// printf("%c\n", line[(*i)]);
		// add check for tabs and jump a lot of tabs
		j = *i + 1 + skip_char(line, ' ');
		while (line[(*i)] != '\n')
		{
			len++;
			(*i)++;
		}
		temp = ft_substr(line, j, len);
		// printf("esse eh o TEMP %s--\n", temp);
	}
	(*i)++;
	return (temp);
}

bool	file_checker(t_file *valid_file)
{
	int	i;

	i = 0;
	while (valid_file->file[i])
	{
		valid_file->NO = textures_checker(valid_file->file, &i, "NO");
		valid_file->SO = textures_checker(valid_file->file, &i, "SO");
		valid_file->WE = textures_checker(valid_file->file, &i, "WE");
		valid_file->EA = textures_checker(valid_file->file, &i, "EA");
		printf("%s--\n", valid_file->NO);
		printf("%s--\n", valid_file->SO);
		printf("%s--\n", valid_file->WE);
		printf("%s--\n", valid_file->EA);
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

void	file_validator(char *argv, t_file *valid_file)
{
	if (file_extension_checker(&argv[1]) == false)
		exit(EXIT_FAILURE);
	valid_file->file = read_file(argv);
	if (valid_file->file == NULL)
		error_message("Something wrong reading the file");
	// printf("%s---\n", valid_file->file);
	file_checker(valid_file);
	// printf("oq tem dentro do WE = %s\n", valid_file->WE);
}
