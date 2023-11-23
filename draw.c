#include "cub3D.h"

int ft_get_color(t_progr *cube, t_element *node, double x_p, double y_p)
{
    int color;

    cube = cube;
    x_p = x_p;
    y_p = y_p;

    if (node->side == 1)
    {
        if (node->ray_dir_y < 0)
            color = 10000 + node->wall_x * 100;           // Face au SUD
        if (node->ray_dir_y >= 0)
            color = 30000 + node->wall_x * 100;          // Face au NORD
    }
    else
    {
        if (node->ray_dir_x < 0)
            color = 50000 + node->wall_x * 100;         // Face à l'EST
        if (node->ray_dir_x >= 0)
            color = 70000 + node->wall_x * 100;         // Face à l'OUEST
    }

    return (color);
}

void    ft_draw_2(t_progr *cube, t_element *node, int y_w)
{
    int     x_w;
    double  x_p;
    double  y_p;
    int color;

    x_w = node->index - 1;
    x_p = node->wall_x;
    y_p = ((double)y_w - node->draw_start - 1) / (node->draw_end - node->draw_start);

    color = ft_get_color(cube, node, x_p, y_p);

    ft_put_pixel_to_img(cube, x_w, y_w, color);

    //if (y_w % 100 == 0)
        //printf("\n X = %f : Y = %f : N = %d\n", x_p, y_p, node->draw_end - node->draw_start);
}

void    ft_draw(t_progr *cube, t_element *node)
{
    int i;

    i = node->draw_start;


    while (i <= node->draw_end)
    {
        ft_draw_2(cube, node, i);
        i++;
    }
    //printf("\n END ; X = %f : Y = %f : N = %d\n", node->wall_x, ((double)i - node->draw_start - 1) / (node->draw_end - node->draw_start), node->draw_end - node->draw_start);
}