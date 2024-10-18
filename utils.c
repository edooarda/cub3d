/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 18:32:15 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/18 20:24:19 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message(char *message)
{
	ft_putendl_fd("ERROR", 2);
	ft_putendl_fd(message, 2);
}

void	free_split(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

char	*space_jumper(char *str)
{
	char	*temp;
	int		i;
	int		len;

	i = 2;
	if (str != NULL)
	{
		if (str[i] != ' ' && str[i] != '\t')
			return (free(str), NULL);
		while (str[i] == ' ' || str[i] == '\t')
			i++;
		len = ft_strlen(str);
		temp = malloc(sizeof(char) * len);
		ft_strlcpy(temp, &str[i], len);
		free(str);
		return (temp);
	}
	else
		return (NULL);
}
