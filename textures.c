/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:45:17 by cmansey           #+#    #+#             */
/*   Updated: 2023/12/03 13:31:15 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Charge une texture et stocke ses données
int	load_texture(t_texture *texture, char *file_path, void *mlx_ptr)
{
	int		bpp;
	int		size_line;
	int		endian;

	texture->img_ptr = mlx_xpm_file_to_image(mlx_ptr, file_path,
			&texture->width, &texture->height);
	if (!texture->img_ptr)
	{
		printf("Error\nInvalid textures\n");
		exit (EXIT_FAILURE);
	}
	texture->data = (unsigned int *)mlx_get_data_addr(texture->img_ptr,
			&bpp, &size_line, &endian);
	return (1);
}

// Charge toutes les textures nécessaires
int	ft_textures(t_mapp *config, t_progr *prog)
{
	if (!load_texture(&(config->north_texture),
			config->north_texture_path, prog->mlx))
		return (0);
	if (!load_texture(&(config->south_texture),
			config->south_texture_path, prog->mlx))
		return (0);
	if (!load_texture(&(config->west_texture),
			config->west_texture_path, prog->mlx))
		return (0);
	if (!load_texture(&(config->east_texture),
			config->east_texture_path, prog->mlx))
		return (0);
	return (1);
}

// Récupère la couleur d'un pixel spécifique dans la texture
unsigned int	get_pixel_color(t_texture *texture, int x, int y)
{
	if (x < 0 || x >= texture->width || y < 0 || y >= texture->height)
		return (0);
	return (texture->data[y * texture->width + x]);
}
