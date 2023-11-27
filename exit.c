/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:55:12 by cmansey           #+#    #+#             */
/*   Updated: 2023/11/26 20:25:57 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_textures(t_mapp *config)
{
	if (config->north_texture_path != NULL)
		free(config->north_texture_path);
	if (config->south_texture_path != NULL)
		free(config->south_texture_path);
	if (config->west_texture_path != NULL)
		free(config->west_texture_path);
	if (config->east_texture_path != NULL)
		free(config->east_texture_path);
	config->north_texture_path = NULL;
	config->south_texture_path = NULL;
	config->west_texture_path = NULL;
	config->east_texture_path = NULL;
}

void	free_map_array(char **map_array, int map_size)
{
	int	i;

	i = 0;
	while (i < map_size)
	{
		free(map_array[i]);
		i++;
	}
	free(map_array);
}

