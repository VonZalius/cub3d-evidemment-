/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:04:31 by cmansey           #+#    #+#             */
/*   Updated: 2023/11/27 21:22:37 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	map_key_to_index(int keycode)
{
	switch (keycode)
	{
		case 65307: return KEY_ESC; // Exemple: KEY_ESC pourrait être 1
		case 65361: return KEY_LEFT; // Exemple: KEY_LEFT pourrait être 2
		case 65363: return KEY_RIGHT; // Exemple: KEY_RIGHT pourrait être 3
		case 119: return KEY_W; // Exemple: KEY_W pourrait être 4
		case 97: return KEY_A; // Exemple: KEY_A pourrait être 5
		case 115: return KEY_S; // Exemple: KEY_S pourrait être 6
		case 100: return KEY_D; // Exemple: KEY_D pourrait être 7
		default: return keycode; // Pour les touches standard
	}
}

/*int	key_press_handler(int key, t_progr *progr)
{
	progr->key_states[key] = 1;
	return (0);
}

int	key_release_handler(int key, t_progr *progr)
{
	progr->key_states[key] = 0;
	return (0);
}*/

int	key_press_handler(int keycode, t_progr *progr)
{
	int	index;

	index = map_key_to_index(keycode);
	if (index >= 0 && index < 256)
		progr->key_states[index] = 1;
	return (0);
}

int	key_release_handler(int keycode, t_progr *progr)
{
	int	index;

	index = map_key_to_index(keycode);
	if (index >= 0 && index < 256)
		progr->key_states[index] = 0;
	return (0);
}

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
	//printf("XXXXX %f %f\n", x, y);
	return (ft_is_wall((int)x, (int)y, progr));
}

int	ft_input(t_progr *progr)
{
	double	save;
	double	xs;
	double	ys;

	xs = progr->player.co_x;
	ys = progr->player.co_y;

	//printf ("HELLO\n");
	//mlx_clear_window(progr->mlx, progr->window.ref);
	if (progr->key_states[KEY_D] == 1)
	{
		xs -= progr->player.vue_y * progr->player.speed * 10;
		ys += progr->player.vue_x * progr->player.speed * 10;
		if (ft_collide(xs, ys, progr) == 0)
		{
			progr->player.co_x = xs;
			progr->player.co_y = ys;
		}
	}
	if (progr->key_states[KEY_A] == 1)
	{
		xs += progr->player.vue_y * progr->player.speed * 10;
		ys -= progr->player.vue_x * progr->player.speed * 10;
		if (ft_collide(xs, ys, progr) == 0)
		{
			progr->player.co_x = xs;
			progr->player.co_y = ys;
		}
	}
	if (progr->key_states[KEY_S] == 1)
	{
		xs -= progr->player.vue_x * progr->player.speed * 10;
		ys -= progr->player.vue_y * progr->player.speed * 10;
		if (ft_collide(xs, ys, progr) == 0)
		{
			progr->player.co_x = xs;
			progr->player.co_y = ys;
		}
	}
	if (progr->key_states[KEY_W] == 1)
	{
		xs += progr->player.vue_x * progr->player.speed * 10;
		ys += progr->player.vue_y * progr->player.speed * 10;
		if (ft_collide(xs, ys, progr) == 0)
		{
			progr->player.co_x = xs;
			progr->player.co_y = ys;
		}
	}
	if (progr->key_states[KEY_ESC] == 1)
	{
		destroy_textures(&progr->mapp);
		free_map_array(progr->mapp.map_array, progr->mapp.map_size);
		mlx_destroy_window(progr->mlx, progr->window.ref);
		mlx_destroy_display(progr->mlx);
		free(progr->mlx);
		exit(0);
	}
	if (progr->key_states[KEY_RIGHT] == 1) //tourner à droite (ne pas oublier d'ajouter raccourci mac)
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
	if (progr->key_states[KEY_LEFT] == 1) //tourner à gauche (ne pas oublier d'ajouter raccourci mac)
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
	/*change color based on keys R, G and B.
	else if (key == 114)
		turn_img_to_color(&progr->img, new_color(255,0,0,0));
	else if (key == 103)
		turn_img_to_color(&progr->img, new_color(0,255,0,0));
	else if (key == 98)
		turn_img_to_color(&progr->img, new_color(0,0,255,0));*/
	return (0);
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
	/*ft_put_pixel_to_img(progr, progr->player.co_x + progr->player.vue_x * 10, progr->player.co_y + progr->player.vue_y * 10, 0xFFFFFF);
	ft_put_pixel_to_img(progr, progr->player.co_x + progr->player.plan_x * 10, progr->player.co_y + progr->player.plan_y * 10, 0xFFFFFF);
	ft_put_pixel_to_img(progr, progr->player.co_x - progr->player.plan_x * 10, progr->player.co_y - progr->player.plan_y * 10, 0xFFFFFF);*/
	mlx_put_image_to_window(progr->mlx, progr->window.ref,
		progr->map.image, 0, 0);
	return (0);
}
