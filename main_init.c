/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:02:19 by cmansey           #+#    #+#             */
/*   Updated: 2023/12/03 13:31:09 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	main_init_4(t_progr *progr)
{
	if (progr->mapp.player_dir == 'E')
	{
		progr->player.vue_x = 1;
		progr->player.vue_y = 0;
		progr->player.plan_x = 0;
		progr->player.plan_y = 0.90;
	}
	else if (progr->mapp.player_dir == 'W')
	{
		progr->player.vue_x = -1;
		progr->player.vue_y = 0;
		progr->player.plan_x = 0;
		progr->player.plan_y = -0.90;
	}
}

void	main_init_3(t_progr *progr)
{
	if (progr->mapp.player_dir == 'N')
	{
		progr->player.vue_x = 0;
		progr->player.vue_y = -1;
		progr->player.plan_x = 0.90;
		progr->player.plan_y = 0;
	}
	else if (progr->mapp.player_dir == 'S')
	{
		progr->player.vue_x = 0;
		progr->player.vue_y = 1;
		progr->player.plan_x = -0.90;
		progr->player.plan_y = 0;
	}
	else
		main_init_4(progr);
}

void	main_init_2(t_progr *progr)
{
	progr->window.x = 2200;
	progr->window.y = 1080;
	progr->map.tiles_edge = 100;
	progr->map.celling = progr->mapp.ceiling_color;
	progr->map.floor = progr->mapp.floor_color;
	progr->map.w_x_c = progr->window.x;
	progr->map.w_y_c = progr->window.y;
	progr->player.move = 10;
	progr->player.speed = 0.2;
	progr->player.co_x = progr->mapp.player_pos_y
		* progr->map.tiles_edge + (progr->map.tiles_edge / 2);
	progr->player.co_y = progr->mapp.player_pos_x
		* progr->map.tiles_edge + (progr->map.tiles_edge / 2);
}

int	main_init_1(t_progr *progr, int argc, char **argv)
{
	if (main_parsing(argc, argv, &progr->mapp) == 1)
		return (0);
	main_init_2(progr);
	main_init_3(progr);
	progr->map.map_tab = progr->mapp.map_array;
	progr->map.map = array_to_char(progr->map.map_tab);
	progr->mlx = mlx_init();
	if (!progr->mlx)
	{
		printf("Error\nMlx init failed.\n");
		exit (1);
	}
	progr->map.image = mlx_new_image(progr->mlx,
			progr->window.x, progr->window.y);
	progr->window = ft_new_window(progr, progr->window.x,
			progr->window.y, "cub3D");
	progr->element = creer_liste(progr->map.w_x_c);
	return (1);
}
