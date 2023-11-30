/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:04:31 by cmansey           #+#    #+#             */
/*   Updated: 2023/11/28 00:38:53 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void    ft_animation(t_progr *progr)
{
    static int  k;
    int         color;
    int         i;
    int         j;

    i = 0;
    while (i != 64)
    {
        j = 0;
        while (j != 64)
        {
            if(k < 100)
                color = get_pixel_color(&progr->mapp.north_texture, i, j);
            else
                color = get_pixel_color(&progr->mapp.south_texture, i, j);
            ft_put_pixel_to_img(progr, i + progr->map.w_x_c - 100, j + progr->map.w_y_c - 100, color);
            j++;
        }
        i++;
    }
    k++;
    if (k > 200)
        k = 0;
}