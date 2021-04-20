#include "cub3d.h"
#define FOV 0.5

void            my_mlx_pixel_put(t_data data, int x, int y, int color)
{
    char    *dst;

    dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void            dl(t_data data, int current_x, int start_y, int end_y, int color)
{
    char    *dst;
    while (start_y < end_y)
    {
        dst = data.addr + (start_y * data.line_length + current_x * (data.bits_per_pixel / 8));
        *(unsigned int*)dst = color;
        start_y++;
    }
}