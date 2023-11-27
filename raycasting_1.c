/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 20:14:49 by cmansey           #+#    #+#             */
/*   Updated: 2023/11/26 20:26:12 by cmansey          ###   ########.fr       */
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

void	initial_step(t_progr *cube, t_element *node)
{
	if (node->ray_dir_x < 0)
	{
		node->step_x = -1;
		node->side_x = ((cube->player.co_x / cube->map.tiles_edge)
				- node->map_x) * node->delta_x;
	}
	else
	{
		node->step_x = 1;
		node->side_x = (node->map_x + 1.0 - (cube->player.co_x
					/ cube->map.tiles_edge)) * node->delta_x;
	}
	if (node->ray_dir_y < 0)
	{
		node->step_y = -1;
		node->side_y = ((cube->player.co_y / cube->map.tiles_edge)
				- node->map_y) * node->delta_y;
	}
	else
	{
		node->step_y = 1;
		node->side_y = (node->map_y + 1.0 - (cube->player.co_y
					/ cube->map.tiles_edge)) * node->delta_y;
	}
}

void	dda(t_progr *cube, t_element *node)
{
	while (node->hit == 0)
	{
		if (node->side_x < node->side_y)
		{
			node->side_x += node->delta_x;
			node->map_x += node->step_x;
			node->side = 0;
		}
		else
		{
			node->side_y += node->delta_y;
			node->map_y += node->step_y;
			node->side = 1;
		}
		//printf ("XXXXXFFF %i %i\n", node->map_y, node->map_x);
		if (cube->map.map_tab[node->map_y][node->map_x] == '1')
		{
			//printf ("FFF\n");
			node->hit = 1;
		}
	}
}

void	calc_final_ray(t_progr *cube, t_element *node)
{
	if (node->side == 0)
	{
		node->perp_wall_dist = (node->map_x
				- (cube->player.co_x / cube->map.tiles_edge)
				+ (1 - node->step_x) / 2) / node->ray_dir_x;
		node->wall_x = (cube->player.co_y / cube->map.tiles_edge)
			+ node->perp_wall_dist * node->ray_dir_y;
	}
	else
	{
		node->perp_wall_dist = (node->map_y
				- (cube->player.co_y / cube->map.tiles_edge)
				+ (1 - node->step_y) / 2) / node->ray_dir_y;
		node->wall_x = (cube->player.co_x / cube->map.tiles_edge)
			+ node->perp_wall_dist * node->ray_dir_x;
	}
	node->wall_x -= floor(node->wall_x);
	node->line_height = (int)(cube->map.w_y_c / node->perp_wall_dist);
	node->draw_start = (((-node->line_height) / 2) + (cube->map.w_y_c / 2));
	if (node->draw_start < 0)
		node->draw_start = 0;
	node->draw_end = ((node->line_height / 2) + (cube->map.w_y_c / 2));
	if (node->draw_end >= cube->map.w_y_c)
		node->draw_end = cube->map.w_y_c - 1;
}

void	init_zero(t_element *node)
{
	node->ray_dir_x = 0;
	node->ray_dir_y = 0;
	node->perp_wall_dist = 0;
	node->side = 0;
	node->line_height = 0;
	node->draw_start = 0;
	node->draw_end = 0;
	node->cam_x = 0;
	node->side_x = 0;
	node->side_y = 0;
	node->step_x = 0;
	node->step_y = 0;
	node->delta_y = 0;
	node->delta_x = 0;
	node->hit = 0;
	node->map_x = 0;
	node->map_y = 0;
	node->wall_x = 0;
}

void	raycasting(t_progr *cube)
{
	t_element	*node;

	//printf ("XXXXX 0\n");
	node = cube->element;
	while (node)
	{
		//printf ("XXXXX 1\n");
		init_zero(node);
		//printf ("XXXXX 2\n");
		init_for_calc(cube, node);
		//printf ("XXXXX 3\n");
		initial_step(cube, node);
		//printf ("XXXXX 4\n");
		dda(cube, node);
		//printf ("XXXXX 5\n");
		calc_final_ray(cube, node);
		ft_draw(cube, node);
		//if (node->suivant == NULL)
		//	printf ("Hello\n ray_dir_x %f\n ray_dir_y %f\n Perp_wall_dist %f\n side %i\n line_height %i\n cam_x %f\n side_x %f\n side_y %f\n step_x %i\n step_y %i\n delta_x %f\n delta_y %f\n hit %i\n wall_x %f\n", node->ray_dir_x, node->ray_dir_y, node->perp_wall_dist, node->side, node->line_height, node->cam_x, node->side_x, node->side_y, node->step_x, node->step_y, node->delta_x, node->delta_y, node->hit, node->wall_x);
		node = node->suivant;
	}
	//printf ("Hello\n ray_dir_x %f\n ray_dir_y %f\n Perp_wall_dist %f\n side %i\n line_height %i\n cam_x %f\n side_x %f\n side_y %f\n step_x %i\n step_y %i\n delta_x %f\n delta_y %f\n hit %i\n wall_x %f\n", node->ray_dir_x, node->ray_dir_y, node->perp_wall_dist, node->side, node->line_height, node->cam_x, node->side_x, node->side_y, node->step_x, node->step_y, node->delta_x, node->delta_y, node->hit, node->wall_x);
	//printf ("XXXXX 6\n");
}
