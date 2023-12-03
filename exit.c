/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 18:55:12 by cmansey           #+#    #+#             */
/*   Updated: 2023/12/03 13:34:00 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	destroy_textures_bis(t_mapp *config)
{
	if (config->west_texture.img_ptr != NULL)
	{
		mlx_destroy_image(NULL, config->west_texture.img_ptr);
		config->west_texture.img_ptr = NULL;
	}
	if (config->west_texture_path != NULL)
	{
		free(config->west_texture_path);
		config->west_texture_path = NULL;
	}
	if (config->east_texture.img_ptr != NULL)
	{
		mlx_destroy_image(NULL, config->east_texture.img_ptr);
		config->east_texture.img_ptr = NULL;
	}
	if (config->east_texture_path != NULL)
	{
		free(config->east_texture_path);
		config->east_texture_path = NULL;
	}
}

void	destroy_textures(t_progr *progr, t_mapp *config)
{
	if (progr->mlx)
		return ;
	if (config->north_texture.img_ptr != NULL)
	{
		mlx_destroy_image(NULL, config->north_texture.img_ptr);
		config->north_texture.img_ptr = NULL;
	}
	if (config->north_texture_path != NULL)
	{
		free(config->north_texture_path);
		config->north_texture_path = NULL;
	}
	if (config->south_texture.img_ptr != NULL)
	{
		mlx_destroy_image(NULL, config->south_texture.img_ptr);
		config->south_texture.img_ptr = NULL;
	}
	if (config->south_texture_path != NULL)
	{
		free(config->south_texture_path);
		config->south_texture_path = NULL;
	}
	destroy_textures_bis(config);
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
