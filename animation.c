/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:04:31 by cmansey           #+#    #+#             */
/*   Updated: 2023/12/03 13:30:49 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_animation(t_progr *progr)
{
	static int	k;
	int			color;
	int			i;
	int			j;

	i = -1;
	while (++i != progr->mapp.north_texture.height)
	{
		j = -1;
		while (++j != progr->mapp.north_texture.height)
		{
			if (k < 100)
				color = get_pixel_color(&progr->mapp.north_texture, i, j);
			else if (k < 200)
				color = get_pixel_color(&progr->mapp.east_texture, i, j);
			else if (k < 300)
				color = get_pixel_color(&progr->mapp.south_texture, i, j);
			else
				color = get_pixel_color(&progr->mapp.west_texture, i, j);
			ft_put_pixel_to_img(progr, i + progr->map.w_x_c - 100,
				j + progr->map.w_y_c - 100, color);
		}
	}
	if (k++ > 400)
		k = 0;
}
