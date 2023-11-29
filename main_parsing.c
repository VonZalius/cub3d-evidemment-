/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:02:19 by cmansey           #+#    #+#             */
/*   Updated: 2023/11/29 19:28:24 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_check_args(int argc, char **argv)
{
	if (argc != 2)
	{
		printf("Error\nInvalid number of arguments.\nInsert only one map.\n");
		exit (1);
	}
	if (!ft_strnstr(argv[1], ".cub", ft_strlen(argv[1])))
	{
		printf("Error\nInvalid type of file.\nInsert .cub file.\n");
		exit (1);
	}
}

void	ft_init(t_mapp *config)
{
	config->north_texture_path = NULL;
	config->south_texture_path = NULL;
	config->west_texture_path = NULL;
	config->east_texture_path = NULL;
	config->floor_color = -1;
	config->ceiling_color = -1;
	config->map_array = NULL;
	config->map_size = 0;
	config->config_done = 0;
	config->player_pos_x = -1;
	config->player_pos_y = -1;
	config->player_dir = '\0';
	config->north_texture.img_ptr = NULL;
	config->south_texture.img_ptr = NULL;
	config->west_texture.img_ptr = NULL;
	config->east_texture.img_ptr = NULL;
}

int	main_parsing(int argc, char **argv, t_mapp *config)
{
	//t_progr	progr;
	//t_mapp	config;

	ft_check_args(argc, argv);
	ft_init(config);
	ft_check_file(argv, config);
	if (ft_map_valid(config) == 1)
	{
		/*progr.mlx = mlx_init();
		progr.window = ft_new_window(progr.mlx, 1980, 1080, "so_long");
		progr.img = ft_new_sprite(progr.mlx, "xpm/player.xpm");
		progr.img_position.x = 100;
		progr.img_position.y = 100;
		mlx_put_image_to_window(progr.mlx, progr.window.ref,
			progr.img.ref, progr.img_position.x, progr.img_position.y);
		mlx_key_hook(progr.window.ref, *ft_input, &progr);
		mlx_loop_hook(progr.mlx, *ft_anime, &progr);
		mlx_loop(progr.mlx);*/
		return (0);
	}
	else
	{
		printf("Error\nMap is not valid.\n");
		/*free_map_array(config->map_array, config->map_size);
		free(config->north_texture_path);
		free(config->south_texture_path);
		free(config->west_texture_path);
		free(config->east_texture_path);
		free(config);*/
		return (1);
	}
}
