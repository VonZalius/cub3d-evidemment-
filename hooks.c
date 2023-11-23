/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:04:31 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/31 17:19:22 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Any functon that you hook with the key event must be like this:
* Recibing and int for the code of the key pressed
* and a void pointer in case you need to recibe someting */

int ft_is_wall(int x, int y, t_progr *progr)
{
	int	i;

	i = 0;
	x = x / progr->map.tiles_edge;
	y = y / progr->map.tiles_edge;
	while (y > 0)
	{
		while(progr->map.map[i] != '\n' && progr->map.map[i] != '\0')
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
			if (ft_is_wall(j * progr->map.tiles_edge, k * progr->map.tiles_edge, progr) == 1)
			{
				printf("SALUUT 4\n");
				ft_put_pixel_to_img(progr, j * 10, k * 10, 0xFFFFFF);
				ft_put_pixel_to_img(progr, (j + 0.5) * 10, k * 10, 0xFFFFFF);
				ft_put_pixel_to_img(progr, (j + 1) * 10, k * 10, 0xFFFFFF);
				ft_put_pixel_to_img(progr, j * 10, (k + 0.5) * 10, 0xFFFFFF);
				ft_put_pixel_to_img(progr, j * 10, (k + 1) * 10, 0xFFFFFF);
				ft_put_pixel_to_img(progr, (j + 0.5) * 10, (k + 1) * 10, 0xFFFFFF);
				ft_put_pixel_to_img(progr, (j + 1) * 10, (k + 0.5) * 10, 0xFFFFFF);
				ft_put_pixel_to_img(progr, (j + 1) * 10, (k + 1) * 10, 0xFFFFFF);
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

int	ft_input(int key, t_progr *progr)
{
	double save;
	double xs;
	double ys;

	xs = progr->player.co_x;
	ys = progr->player.co_y;

	//printf ("HELLO\n");
	mlx_clear_window(progr->mlx, progr->window.ref);
	if (key == 2 || key == 100)
	{
		xs -= progr->player.vue_y * progr->player.speed * 10;
		ys += progr->player.vue_x * progr->player.speed * 10;
		if(ft_collide(xs, ys, progr) == 0)
		{
			progr->player.co_x = xs;
			progr->player.co_y = ys;
		}
	}
	else if (key == 0 || key == 97)
	{
		xs += progr->player.vue_y * progr->player.speed * 10;
		ys -= progr->player.vue_x * progr->player.speed * 10;
		if(ft_collide(xs, ys, progr) == 0)
		{
			progr->player.co_x = xs;
			progr->player.co_y = ys;
		}
	}
	else if (key == 1 || key == 115)
	{
		xs -= progr->player.vue_x * progr->player.speed * 10;
		ys -= progr->player.vue_y * progr->player.speed * 10;
		if(ft_collide(xs, ys, progr) == 0)
		{
			progr->player.co_x = xs;
			progr->player.co_y = ys;
		}
	}
	else if (key == 13 || key == 119)
	{
		xs += progr->player.vue_x * progr->player.speed * 10;
		ys += progr->player.vue_y * progr->player.speed * 10;
		if(ft_collide(xs, ys, progr) == 0)
		{
			progr->player.co_x = xs;
			progr->player.co_y = ys;
		}
	}
	else if (key == 53 || key == 65307)
		exit(0);
	else if (key == 65363) //tourner à droite (ne pas oublier d'ajouter raccourci mac)
	{
		save = progr->player.vue_x;
		progr->player.vue_x = progr->player.vue_x * cos(progr->player.speed / 4) - progr->player.vue_y * sin(progr->player.speed / 4);
		progr->player.vue_y = save * sin(progr->player.speed / 4) + progr->player.vue_y * cos(progr->player.speed / 4);
		save = progr->player.plan_x;
		progr->player.plan_x = progr->player.plan_x * cos(progr->player.speed / 4) - progr->player.plan_y * sin(progr->player.speed / 4);
		progr->player.plan_y = save * sin(progr->player.speed / 4) + progr->player.plan_y * cos(progr->player.speed / 4);
	}
	else if (key == 65361) //tourner à gauche (ne pas oublier d'ajouter raccourci mac)
	{
		save = progr->player.vue_x;
		progr->player.vue_x = progr->player.vue_x * cos(-progr->player.speed / 4) - progr->player.vue_y * sin(-progr->player.speed / 4);
		progr->player.vue_y = save * sin(-progr->player.speed / 4) + progr->player.vue_y * cos(-progr->player.speed / 4);
		save = progr->player.plan_x;
		progr->player.plan_x = progr->player.plan_x * cos(-progr->player.speed / 4) - progr->player.plan_y * sin(-progr->player.speed / 4);
		progr->player.plan_y = save * sin(-progr->player.speed / 4) + progr->player.plan_y * cos(-progr->player.speed / 4);
	}
			/*change color based on keys R, G and B.
	else if (key == 114)
		turn_img_to_color(&progr->img, new_color(255,0,0,0));
	else if (key == 103)
		turn_img_to_color(&progr->img, new_color(0,255,0,0));
	else if (key == 98)
		turn_img_to_color(&progr->img, new_color(0,0,255,0));*/
	ft_remplissage(progr);
	raycasting(progr);
	ft_put_wall(progr);
	ft_put_pixel_to_img(progr, (progr->player.co_x / 10), (progr->player.co_y / 10) + 1, 0xFFFFFF);
	ft_put_pixel_to_img(progr, (progr->player.co_x / 10) + 1, (progr->player.co_y / 10), 0xFFFFFF);
	ft_put_pixel_to_img(progr, (progr->player.co_x / 10), (progr->player.co_y / 10) - 1, 0xFFFFFF);
	ft_put_pixel_to_img(progr, (progr->player.co_x / 10) - 1, (progr->player.co_y / 10), 0xFFFFFF);
	/*ft_put_pixel_to_img(progr, progr->player.co_x + progr->player.vue_x * 10, progr->player.co_y + progr->player.vue_y * 10, 0xFFFFFF);	
	ft_put_pixel_to_img(progr, progr->player.co_x + progr->player.plan_x * 10, progr->player.co_y + progr->player.plan_y * 10, 0xFFFFFF);
	ft_put_pixel_to_img(progr, progr->player.co_x - progr->player.plan_x * 10, progr->player.co_y - progr->player.plan_y * 10, 0xFFFFFF);*/
	mlx_put_image_to_window(progr->mlx, progr->window.ref, progr->map.image, 0, 0);



	printf("Key pressed -> %d\n", key);
	return (0);
}
