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

void ft_input_3(t_progr *progr, double xs, double ys)
{
	if (ft_collide(xs, ys, progr) == 0)
		{
			progr->player.co_x = xs;
			progr->player.co_y = ys;
		}
}

void ft_input_2(t_progr *progr, double xs, double ys)
{
	if (progr->key_states[KEY_D] == 1)
	{
		xs -= progr->player.vue_y * progr->player.speed * 10;
		ys += progr->player.vue_x * progr->player.speed * 10;
		ft_input_3(progr, xs, ys);
	}
	if (progr->key_states[KEY_A] == 1)
	{
		xs += progr->player.vue_y * progr->player.speed * 10;
		ys -= progr->player.vue_x * progr->player.speed * 10;
		ft_input_3(progr, xs, ys);
	}
	if (progr->key_states[KEY_S] == 1)
	{
		xs -= progr->player.vue_x * progr->player.speed * 10;
		ys -= progr->player.vue_y * progr->player.speed * 10;
		ft_input_3(progr, xs, ys);
	}
	if (progr->key_states[KEY_W] == 1)
	{
		xs += progr->player.vue_x * progr->player.speed * 10;
		ys += progr->player.vue_y * progr->player.speed * 10;
		ft_input_3(progr, xs, ys);
	}
}

void	ft_input_5(t_progr *progr, double	save)
{
	if (progr->key_states[KEY_LEFT] == 1)
	{
		save = progr->player.vue_x;
		progr->player.vue_x = progr->player.vue_x
			* cos(-progr->player.speed / 4) - progr->player.vue_y
			* sin(-progr->player.speed / 4);
		progr->player.vue_y = save * sin(-progr->player.speed / 4)
			+ progr->player.vue_y * cos(-progr->player.speed / 4);
		save = progr->player.plan_x;
		progr->player.plan_x = progr->player.plan_x
			* cos(-progr->player.speed / 4) - progr->player.plan_y
			* sin(-progr->player.speed / 4);
		progr->player.plan_y = save * sin(-progr->player.speed / 4)
			+ progr->player.plan_y * cos(-progr->player.speed / 4);
	}
}

void	ft_input_4(t_progr *progr, double	save)
{
	if (progr->key_states[KEY_RIGHT] == 1)
	{
		save = progr->player.vue_x;
		progr->player.vue_x = progr->player.vue_x
			* cos(progr->player.speed / 4) - progr->player.vue_y
			* sin(progr->player.speed / 4);
		progr->player.vue_y = save * sin(progr->player.speed / 4)
			+ progr->player.vue_y * cos(progr->player.speed / 4);
		save = progr->player.plan_x;
		progr->player.plan_x = progr->player.plan_x
			* cos(progr->player.speed / 4) - progr->player.plan_y
			* sin(progr->player.speed / 4);
		progr->player.plan_y = save * sin(progr->player.speed / 4)
			+ progr->player.plan_y * cos(progr->player.speed / 4);
	}
}

int	ft_input(t_progr *progr)
{
	double	save;
	double	xs;
	double	ys;

	xs = progr->player.co_x;
	ys = progr->player.co_y;
	ft_input_2(progr, xs, ys);
	if (progr->key_states[KEY_ESC] == 1)
	{
		destroy_textures(progr->mlx, &progr->mapp);
		free_map_array(progr->mapp.map_array, progr->mapp.map_size);
		mlx_destroy_window(progr->mlx, progr->window.ref);
		mlx_destroy_display(progr->mlx);
		free(progr->mlx);
		exit(0);
	}
	ft_input_4(progr, save);
	ft_input_5(progr, save);
	return (0);
}