/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:04:31 by cmansey           #+#    #+#             */
/*   Updated: 2023/12/03 13:19:50 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	ft_is_wall(int x, int y, t_progr *progr)
{
	int	i;

	i = 0;
	x = x / progr->map.tiles_edge;
	y = y / progr->map.tiles_edge;
	while (y > 0)
	{
		while (progr->map.map[i] != '\n' && progr->map.map[i] != '\0')
			i++;
		i++;
		y--;
	}
	while (x > 0)
	{
		i++;
		x--;
	}
	if (progr->map.map[i] == '1')
		return (1);
	return (0);
}

void	ft_put_wall_bis(t_progr *progr, int j, int k)
{
	ft_put_pixel_to_img(progr, j * 10, k * 10, 0xFFFFFF);
	ft_put_pixel_to_img(progr, (j + 0.5) * 10, k * 10, 0xFFFFFF);
	ft_put_pixel_to_img(progr, (j + 1) * 10, k * 10, 0xFFFFFF);
	ft_put_pixel_to_img(progr, j * 10, (k + 0.5) * 10, 0xFFFFFF);
	ft_put_pixel_to_img(progr, j * 10, (k + 1) * 10, 0xFFFFFF);
	ft_put_pixel_to_img(progr, (j + 0.5)
		* 10, (k + 1) * 10, 0xFFFFFF);
	ft_put_pixel_to_img(progr, (j + 1)
		* 10, (k + 0.5) * 10, 0xFFFFFF);
	ft_put_pixel_to_img(progr, (j + 1)
		* 10, (k + 1) * 10, 0xFFFFFF);
}

void	ft_put_wall(t_progr *progr)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (progr->map.map[i] != '\0')
	{
		j = 0;
		while (progr->map.map[i] != '\n')
		{
			if (ft_is_wall(j * progr->map.tiles_edge, k
					* progr->map.tiles_edge, progr) == 1)
				ft_put_wall_bis(progr, j, k);
			i++;
			j++;
		}
		i++;
		k++;
	}
}

int	ft_collide(double x, double y, t_progr *progr)
{
	while ((int)x % (int)progr->map.tiles_edge != 0)
		x--;
	while ((int)y % (int)progr->map.tiles_edge != 0)
		y--;
	return (ft_is_wall((int)x, (int)y, progr));
}

int	loop_function(t_progr *progr)
{
	if (ft_input(progr))
		mlx_clear_window(progr->mlx, progr->window.ref);
	ft_remplissage(progr);
	raycasting(progr);
	ft_put_wall(progr);
	ft_put_pixel_to_img(progr, (progr->player.co_x / 10),
		(progr->player.co_y / 10) + 1, 0xFFFFFF);
	ft_put_pixel_to_img(progr, (progr->player.co_x / 10) + 1,
		(progr->player.co_y / 10), 0xFFFFFF);
	ft_put_pixel_to_img(progr, (progr->player.co_x / 10),
		(progr->player.co_y / 10) - 1, 0xFFFFFF);
	ft_put_pixel_to_img(progr, (progr->player.co_x / 10) - 1,
		(progr->player.co_y / 10), 0xFFFFFF);
	ft_animation(progr);
	mlx_put_image_to_window(progr->mlx, progr->window.ref,
		progr->map.image, 0, 0);
	return (0);
}
