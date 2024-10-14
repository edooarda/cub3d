/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: edribeir <edribeir@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/10/09 18:32:15 by edribeir      #+#    #+#                 */
/*   Updated: 2024/10/14 15:41:48 by edribeir      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	error_message(char *message)
{
	ft_putendl_fd("ERROR", 2);
	ft_putendl_fd(message, 2);
	exit(EXIT_FAILURE);
}

void	free_split(char **array)
{
	int i;

	i = 0;
	while(array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}