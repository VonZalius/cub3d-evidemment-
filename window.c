/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:02:51 by cmansey           #+#    #+#             */
/*   Updated: 2023/11/28 00:38:55 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_put_pixel_to_img(t_progr *progr, int x, int y, int color)
{
	int		pixel_bits;
	int		line_bytes;
	int		endian;
	char	*buffer;
	int		pixel;

	buffer = mlx_get_data_addr(progr->map.image,
			&pixel_bits, &line_bytes, &endian);
	if (pixel_bits != 32)
		color = mlx_get_color_value(progr->mlx, color);
	pixel = (y * line_bytes) + (x * 4);
	if (endian == 1)
	{
		buffer[pixel + 0] = (color >> 24);
		buffer[pixel + 1] = (color >> 16) & 0xFF;
		buffer[pixel + 2] = (color >> 8) & 0xFF;
		buffer[pixel + 3] = (color) & 0xFF;
	}
	else if (endian == 0)
	{
		buffer[pixel + 0] = (color) & 0xFF;
		buffer[pixel + 1] = (color >> 8) & 0xFF;
		buffer[pixel + 2] = (color >> 16) & 0xFF;
		buffer[pixel + 3] = (color >> 24);
	}
}

void	ft_remplissage(t_progr *progr)
{
	int	y;
	int	x;

	y = 0;
	while (y < (progr->map.w_y_c / 2))
	{
		x = 0;
		while (x < progr->map.w_x_c)
		{
			ft_put_pixel_to_img(progr, x, y, progr->map.celling);
			x++;
		}
		y++;
	}
	while (y < progr->map.w_y_c)
	{
		x = 0;
		while (x < progr->map.w_x_c)
		{
			ft_put_pixel_to_img(progr, x, y, progr->map.floor);
			x++;
		}
		y++;
	}
}

	///PENSER A FREE ICI AUSSI
int	ft_close(t_progr *progr)
{
	destroy_textures(progr->mlx, &progr->mapp);
	free_map_array(progr->mapp.map_array, progr->mapp.map_size);
	mlx_destroy_window(progr->mlx, progr->window.ref);
	free(progr->mlx);
	exit (0);
}

t_window	ft_new_window(t_progr *progr, int widht, int height, char *name)
{
	t_window	window;

	window.ref = mlx_new_window(progr->mlx, widht, height, name);
	mlx_hook(window.ref, 17, 0, ft_close, progr);
	return (window);
}
