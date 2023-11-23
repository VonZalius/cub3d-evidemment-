/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:02:19 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/31 17:35:25 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*void	ft_check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments.\n");
		exit (1);
	}
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		printf("Error\nInvalid type of file.\nInsert .cub file\n");
		exit (1);
	}
}*/

/*void	ft_check_map(char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
	{
		write(2, "Error\nMap not found.\n", 21);
		exit (1);
	}
}*/

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
		while(array[i][j] != '\0')
		{
			k++;
			j++;
		}
		i++;
	}
	cha = malloc(sizeof(char) * k + 1);
	i = 0;
	k = 0;
	while (array[i] != NULL)
	{
		j = 0;
		while(array[i][j] != '\0')
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

int	main(int argc, char **argv)
{
	t_progr	progr;
	t_mapp	parsing;

	//ft_check_args(argc, argv);
	//ft_check_map(argv);

	if (main_parsing(argc, argv, &parsing) == 1)
		return (0);



	/*---------- Window init ----------*/
	progr.window.x = 2200;
	progr.window.y = 1080;

	/*---------- Map init ----------*/
	progr.map.tiles_edge = 100;
	progr.map.celling = parsing.ceiling_color;
	progr.map.floor = parsing.floor_color;
	progr.map.w_x_c = progr.window.x;
	progr.map.w_y_c = progr.window.y;

	/*---------- Player init ----------*/
	progr.player.move = 10;
	progr.player.speed = 0.7;
	//printf ("PLAYER %i %i\n", parsing.player_pos_x, parsing.player_pos_x);
	progr.player.co_x = parsing.player_pos_y * progr.map.tiles_edge + (progr.map.tiles_edge / 2);
	progr.player.co_y = parsing.player_pos_x * progr.map.tiles_edge + (progr.map.tiles_edge / 2);
	progr.player.vue_x = 0;
	progr.player.vue_y = -1;
	progr.player.plan_x = 0.90;
	progr.player.plan_y = 0;
	
	/*XXXXXXXXXX FAKE WALL XXXXXXXXXX*/
	progr.map.map_tab = parsing.map_array;
	progr.map.map = array_to_char(progr.map.map_tab);
	//printf("XXX %s\n", array_to_char(progr.map.map_tab));

	/*---------- Structs init ----------*/
	progr.mlx = mlx_init();
	progr.map.image = mlx_new_image(progr.mlx, progr.window.x, progr.window.y);
	progr.window = ft_new_window(progr.mlx, progr.window.x, progr.window.y, "cub3D");
    progr.element = creer_liste(progr.map.w_x_c);

	/*progr.img = ft_new_sprite(progr.mlx, "xpm/player.xpm");
	progr.img_position.x = 100;
	progr.img_position.y = 100;*/

	/*mlx_put_image_to_window(progr.mlx, progr.window.ref,
		progr.img.ref, progr.img_position.x, progr.img_position.y);*/

    /*printf("Liste créée : ");
    afficher_liste(progr.element);*/


	ft_remplissage(&progr);



	/*---------- Premier affichage du player ----------*/
	raycasting(&progr);

	/*---------- Mise en place des mures ----------*/
	ft_put_wall(&progr);
	//printf("PUT WALL PASSSSé\n");

	
	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10), (progr.player.co_y / 10) + 1, 0xFFFFFF);
	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10) + 1, (progr.player.co_y / 10), 0xFFFFFF);
	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10), (progr.player.co_y / 10) - 1, 0xFFFFFF);
	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10) - 1, (progr.player.co_y / 10), 0xFFFFFF);
	/*ft_put_pixel_to_img(&progr, progr.player.co_x + progr.player.vue_x * 10, progr.player.co_y + progr.player.vue_y * 10, 0xFFFFFF);
	ft_put_pixel_to_img(&progr, progr.player.co_x + progr.player.plan_x * 10, progr.player.co_y + progr.player.plan_y * 10, 0xFFFFFF);
	ft_put_pixel_to_img(&progr, progr.player.co_x - progr.player.plan_x * 10, progr.player.co_y - progr.player.plan_y * 10, 0xFFFFFF);*/
	mlx_put_image_to_window(progr.mlx, progr.window.ref, progr.map.image, 0, 0);
	/*mlx_pixel_put(progr.mlx, progr.window.ref, progr.player.co_x, progr.player.co_y, 16777215);
	mlx_pixel_put(progr.mlx, progr.window.ref, progr.player.co_x + progr.player.vue_x * 10, progr.player.co_y + progr.player.vue_y * 10, 16777215);
	mlx_pixel_put(progr.mlx, progr.window.ref, progr.player.co_x + progr.player.plan_x * 10, progr.player.co_y + progr.player.plan_y * 10, 16777215);
	mlx_pixel_put(progr.mlx, progr.window.ref, progr.player.co_x - progr.player.plan_x * 10, progr.player.co_y - progr.player.plan_y * 10, 16777215);*/

	mlx_key_hook(progr.window.ref, *ft_input, &progr);
	mlx_loop_hook(progr.mlx, 0, &progr);
	mlx_loop(progr.mlx);

    liberer_liste(progr.element);

	return (0);
}