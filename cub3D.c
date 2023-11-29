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

/*char *array_to_char(char **array) {
    char *cha;
    int i, j, k, total_len;

    // Calculer la taille totale nécessaire
    i = 0;
    total_len = 0;
    while (array[i] != NULL) {
        total_len += strlen(array[i]) + 1; // +1 pour '\n' à la fin de chaque chaîne
        i++;
    }

    // Allouer la mémoire (y compris pour le caractère NULL final)
    cha = malloc(total_len + 1); // +1 pour '\0'
    if (!cha) {
        return (NULL);
    }

    // Copier les chaînes dans cha
    i = 0;
    k = 0;
    while (array[i] != NULL) {
        j = 0;
        while (array[i][j] != '\0') {
            cha[k++] = array[i][j++];
        }
        cha[k++] = '\n'; // Ajouter '\n' à la fin de chaque chaîne
        i++;
    }
    cha[k] = '\0'; // Ajouter le caractère NULL final

    return cha;
}*/

/*char *array_to_char(char **array) {
    char *cha;
    int i, j, k;

    // Calculer la taille nécessaire
    i = 0;
    k = 0;
    while (array[i] != NULL) {
        k += strlen(array[i]) + 1; // +1 pour '\n'
        i++;
    }

    // Allouer la mémoire
    cha = malloc(sizeof(char) * (k + 1)); // +1 pour le caractère NULL final
    if (!cha) {
        return (NULL);
    }

    // Copier les chaînes dans cha
    i = 0;
    k = 0;
    while (array[i] != NULL) {
        j = 0;
        while (array[i][j] != '\0') {
            cha[k++] = array[i][j++];
        }
        cha[k++] = '\n'; // Ajouter '\n' et incrémenter k
        i++;
    }
    cha[k] = '\0'; // S'assurer que le dernier caractère est NULL
    return (cha);
}*/


int	main(int argc, char **argv)
{
	t_progr	progr;
	ft_memset(progr.key_states, 0, sizeof(progr.key_states));
	//t_mapp	parsing;

	//ft_check_args(argc, argv);
	//ft_check_map(argv);

	if (main_parsing(argc, argv, &progr.mapp) == 1)
		return (0);


	/*---------- Window init ----------*/
	progr.window.x = 2200;
	progr.window.y = 1080;

	/*---------- Map init ----------*/
	progr.map.tiles_edge = 100;
	progr.map.celling = progr.mapp.ceiling_color;
	progr.map.floor = progr.mapp.floor_color;
	progr.map.w_x_c = progr.window.x;
	progr.map.w_y_c = progr.window.y;

	/*---------- Player init ----------*/
	progr.player.move = 10;
	progr.player.speed = 0.2;
	//printf ("PLAYER %i %i\n", progr.mapp.player_pos_x, progr.mapp.player_pos_x);
	progr.player.co_x = progr.mapp.player_pos_y
		* progr.map.tiles_edge + (progr.map.tiles_edge / 2);
	progr.player.co_y = progr.mapp.player_pos_x
		* progr.map.tiles_edge + (progr.map.tiles_edge / 2);
	if (progr.mapp.player_dir == 'N')
	{
		progr.player.vue_x = 0;
		progr.player.vue_y = -1;
		progr.player.plan_x = 0.90;
		progr.player.plan_y = 0;
	}
	else if (progr.mapp.player_dir == 'S')
	{
		progr.player.vue_x = 0;
		progr.player.vue_y = 1;
		progr.player.plan_x = -0.90;
		progr.player.plan_y = 0;
	}
	else if (progr.mapp.player_dir == 'E')
	{
		progr.player.vue_x = 1;
		progr.player.vue_y = 0;
		progr.player.plan_x = 0;
		progr.player.plan_y = 0.90;
	}
	else if (progr.mapp.player_dir == 'W')
	{
		progr.player.vue_x = -1;
		progr.player.vue_y = 0;
		progr.player.plan_x = 0;
		progr.player.plan_y = -0.90;
	}

	/*XXXXXXXXXX FAKE WALL XXXXXXXXXX*/
	progr.map.map_tab = progr.mapp.map_array;
	progr.map.map = array_to_char(progr.map.map_tab);

	/*---------- Structs init ----------*/
	progr.mlx = mlx_init();
	if (!progr.mlx)
	{
		printf("Error\nMlx init failed.\n");
		exit (1);
	}
	progr.map.image = mlx_new_image(progr.mlx, progr.window.x, progr.window.y);
	progr.window = ft_new_window(&progr, progr.window.x,
			progr.window.y, "cub3D");
	progr.element = creer_liste(progr.map.w_x_c);

	/*progr.img = ft_new_sprite(progr.mlx, "xpm/player.xpm");
	progr.img_position.x = 100;
	progr.img_position.y = 100;*/

	/*mlx_put_image_to_window(progr.mlx, progr.window.ref,
		progr.img.ref, progr.img_position.x, progr.img_position.y);*/

    /*printf("Liste créée : ");
    afficher_liste(progr.element);*/
	//LIBERER MEMOIRE????
	ft_textures(&progr.mapp, &progr);
	/*if (ft_textures(&progr.mapp, &progr) != 1)
	{
		printf ("No good textures\n");
		int ft_close(t_progr *progr);
		return (0);
	}*/


	ft_remplissage(&progr);



	/*---------- Premier affichage du player ----------*/
	raycasting(&progr);

	/*---------- Mise en place des mures ----------*/
	ft_put_wall(&progr);

	//printf("PUT WALL PASSSSé\n");


	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10),
		(progr.player.co_y / 10) + 1, 0xFFFFFF);
	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10)
		+ 1, (progr.player.co_y / 10), 0xFFFFFF);
	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10),
		(progr.player.co_y / 10) - 1, 0xFFFFFF);
	ft_put_pixel_to_img(&progr, (progr.player.co_x / 10) - 1,
		(progr.player.co_y / 10), 0xFFFFFF);
	/*ft_put_pixel_to_img(&progr, progr.player.co_x + progr.player.vue_x * 10, progr.player.co_y + progr.player.vue_y * 10, 0xFFFFFF);
	ft_put_pixel_to_img(&progr, progr.player.co_x + progr.player.plan_x * 10, progr.player.co_y + progr.player.plan_y * 10, 0xFFFFFF);
	ft_put_pixel_to_img(&progr, progr.player.co_x - progr.player.plan_x * 10, progr.player.co_y - progr.player.plan_y * 10, 0xFFFFFF);*/
	mlx_put_image_to_window(progr.mlx, progr.window.ref, progr.map.image, 0, 0);
	/*mlx_pixel_put(progr.mlx, progr.window.ref, progr.player.co_x, progr.player.co_y, 16777215);
	mlx_pixel_put(progr.mlx, progr.window.ref, progr.player.co_x + progr.player.vue_x * 10, progr.player.co_y + progr.player.vue_y * 10, 16777215);
	mlx_pixel_put(progr.mlx, progr.window.ref, progr.player.co_x + progr.player.plan_x * 10, progr.player.co_y + progr.player.plan_y * 10, 16777215);
	mlx_pixel_put(progr.mlx, progr.window.ref, progr.player.co_x - progr.player.plan_x * 10, progr.player.co_y - progr.player.plan_y * 10, 16777215);*/

	mlx_hook(progr.window.ref, 2, 1L << 0, key_press_handler, &progr);
	mlx_hook(progr.window.ref, 3, 1L << 1, key_release_handler, &progr);
	mlx_loop_hook(progr.mlx, loop_function, &progr);
	//mlx_hook(progr.window.ref, 2, 1L << 0, *ft_input, &progr);
	//mlx_hook(progr.window.ref, 17, 1L << 0, *ft_input, &progr);

	//mlx_key_hook(progr.window.ref, *ft_input, &progr);
	//mlx_loop_hook(progr.mlx, 0, &progr);
	mlx_loop(progr.mlx);
	free(progr.map.map);
	liberer_liste(progr.element);
	return (0);
}
