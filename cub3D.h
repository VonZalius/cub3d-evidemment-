/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmansey <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/31 16:01:23 by cmansey           #+#    #+#             */
/*   Updated: 2023/10/31 17:26:31 by cmansey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

// ----------------------------------
// MACROS

# ifndef ANIMATION_FRAMES
#  define ANIMATION_FRAMES 10
# endif

// ----------------------------------
// STRUCTS

/* vector with an x and y */
typedef struct s_vector {
	int	x;
	int	y;
}				t_vector;

/* A pointer to the window and its size */
typedef struct s_window {
	void		*ref;
	int	x;
	int	y;
}				t_window;

/* The 4 values that define a color */
typedef struct s_color {
	int	r;
	int	g;
	int	b;
	int	a;
}	t_color;

/* all info needed for an image */
typedef struct s_image {
	void		*ref;
	t_vector	size;
	char		*pxl;
	int			bits_pxl;
	int			l_size;
	int			end;
}				t_image;

/* player info */
typedef struct s_player {
	double		move;
	double		speed;
	double		co_x;
	double		co_y;
	double		vue_x;
	double		vue_y;
	double		plan_x;
	double		plan_y;

}				t_player;

/* map info */
typedef struct s_map {
	double		tiles_edge;
	char		*map;
	char		**map_tab;
	void		*image;
	int			celling;
	int			floor;
	int			w_x_c;
	int			w_y_c;
}				t_map;

/*chain element*/
typedef struct s_element {
    int 		index;
	double		ray_dir_x;
	double		ray_dir_y;
	double		perp_wall_dist;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		cam_x;
	double		side_x;
	double		side_y;
	int			step_x;
	int			step_y;
	double		delta_y;
	double		delta_x;
	int			hit;
	int			map_x;
	int			map_y;
	double		wall_x;
    struct s_element* suivant;
}				t_element;

/* MAIN STRUCT */
typedef struct s_progr {
	void		*mlx;
	t_window	window;
	t_image		img;
	t_vector	img_position;
	t_player	player;
	t_map		map;
	t_element	*element;
}				t_progr;

typedef struct s_mapp
{
	char	*north_texture;
	char	*south_texture;
	char	*west_texture;
	char	*east_texture;
	int		floor_color;
	int		ceiling_color;
	char	**map_array;
	int		map_size;
	int		config_done;
	int		player_pos_x;
	int		player_pos_y;
}			t_mapp;
// ---------------------------------
// FUNCTIONS

t_window	ft_new_window(void *mlx, int widht, int height, char *name);
t_image		ft_new_sprite(void *mlx, char *path);
//t_image		ft_new_image(void *mlx, int width, int height);

t_color		new_color(int r, int g, int b, int a);
void		turn_img_to_color(t_image *image, t_color color);

int			ft_input(int key, t_progr *progr);
int			ft_anime(t_progr *progr);

void		ft_put_wall(t_progr *progr);
t_element *creer_liste(int j);
void afficher_liste(t_element *premier);
void liberer_liste(t_element *premier);
void ft_put_pixel_to_img(t_progr *progr, int x, int y, int color);
void ft_remplissage(t_progr *progr);
void	raycasting(t_progr *cube);
void    ft_draw(t_progr *cube, t_element *node);

void		ft_check_file(char **argv, t_mapp *config);
void		parse_file(int fd, t_mapp *config);
int			parse_line(char *line, t_mapp *config);
int			process_map_line(char *line, t_mapp *config);
int			process_texture_and_color(char *line, t_mapp *config);
int			parse_color(char *color_string);
int			is_config_complete(t_mapp *config);
char		**parse_map(char *line, char **map_array, int *size);
char		*skip_spaces(char *str);
char		*convert_tabs_to_spaces(const char *line);
void		replace_tabs_with_spaces(const char *line, char *new_line);
char		*allocate_new_line(const char *line, int tab_count);
int			count_tabs(const char *line);
int			starts_with(const char *line, const char *prefix);
int			ft_map_valid(t_mapp *config);
char		**copy_map_array(t_mapp *config);
void		free_copied_map_array(char **map_copy, int map_size);
int			flood_fill(t_mapp *config, char **map_copy);
int			flood_fill_util(char **map, int x, int y, int map_size);
int			ft_player_valid(t_mapp *config);
int			main_parsing(int argc, char **argv, t_mapp *config);

#endif
