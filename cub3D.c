/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:02:19 by cmansey           #+#    #+#             */
/*   Updated: 2023/11/29 19:44:08 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*array_to_char_bis(char *cha, char **array)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (array[i][j] != '\0')
		{
			cha[k] = array[i][j];
			k++;
			j++;
		}
		cha[k] = '\n';
		i++;
	}
	cha[k] = '\0';
	return (cha);
}

char	*array_to_char(char **array)
{
	char	*cha;
	int		i;
	int		j;
	int		k;

	i = 0;
	k = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while (array[i][j] != '\0')
		{
			k++;
			j++;
		}
		i++;
	}
	cha = malloc(sizeof(char) * k + 1);
	if (!cha)
		return (NULL);
	return (array_to_char_bis(cha, array));
}

int	main(int argc, char **argv)
{
	t_progr	progr;

	ft_memset(progr.key_states, 0, sizeof(progr.key_states));
	if (main_init_1(&progr, argc, argv) == 0)
		return (0);
	ft_textures(&progr.mapp, &progr);
	ft_remplissage(&progr);
	raycasting(&progr);
	ft_put_wall(&progr);
	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10),
		(progr.player.co_y / 10) + 1, 0xFFFFFF);
	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10)
		+ 1, (progr.player.co_y / 10), 0xFFFFFF);
	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10),
		(progr.player.co_y / 10) - 1, 0xFFFFFF);
	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10) - 1,
		(progr.player.co_y / 10), 0xFFFFFF);
	mlx_put_image_to_window(progr.mlx, progr.window.ref, progr.map.image, 0, 0);
	mlx_hook(progr.window.ref, 2, 1L << 0, key_press_handler, &progr);
	mlx_hook(progr.window.ref, 3, 1L << 1, key_release_handler, &progr);
	mlx_loop_hook(progr.mlx, loop_function, &progr);
	mlx_loop(progr.mlx);
	free(progr.map.map);
	liberer_liste(progr.element);
	return (0);
}
