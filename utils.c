/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/17 18:39:02 by cmansey           #+#    #+#             */
/*   Updated: 2023/11/26 18:58:37 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_player_valid(t_mapp *conf)
{
	int		i;
	size_t	j;
	int		player;

	i = 0;
	player = 0;
	while (i < conf->map_size)
	{
		j = 0;
		while (conf->map_array[i][j] != '\0')
		{
			if (conf->map_array[i][j] == 'N' || conf->map_array[i][j] == 'S'
				|| conf->map_array[i][j] == 'W' || conf->map_array[i][j] == 'E')
			{
				player++;
				conf->player_dir = conf->map_array[i][j];
			}
			j++;
		}
		i++;
	}
	if (player == 1)
		return (1);
	else
		return (0);
}

int	contains_digit(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_isdigit(line[i]))
			return (1);
		i++;
	}
	return (0);
}

void	trim_trailing_whitespace(char *str)
{
	int	i;

	i = ft_strlen(str) - 1;
	while (i >= 0 && (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'))
	{
		str[i] = '\0';
		i--;
	}
}

char	*skip_spaces(char *str)
{
	while (*str && (*str == ' ' || *str == '\t'))
		str++;
	return (str);
}

void	free_copied_map_array(char **map_copy, int map_size)
{
	int	i;

	if (map_copy == NULL)
		return ;
	i = 0;
	while (i < map_size)
	{
		free(map_copy[i]);
		i++;
	}
	free(map_copy);
}
