/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:14:49 by cmansey           #+#    #+#             */
/*   Updated: 2023/12/03 13:32:45 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_for_calc(t_progr *cube, t_element *node)
{
	node->cam_x = 2 * node->index / (double)cube->map.w_x_c - 1;
	node->ray_dir_x = cube->player.vue_x + (cube->player.plan_x * node->cam_x);
	node->ray_dir_y = cube->player.vue_y + (cube->player.plan_y * node->cam_x);
	node->delta_y = sqrt(1 + (node->ray_dir_x * node->ray_dir_x)
			/ (node->ray_dir_y * node->ray_dir_y));
	node->delta_x = sqrt(1 + (node->ray_dir_y * node->ray_dir_y)
			/ (node->ray_dir_x * node->ray_dir_x));
	node->map_x = (int)(cube->player.co_x / cube->map.tiles_edge);
	node->map_y = (int)(cube->player.co_y / cube->map.tiles_edge);
}
