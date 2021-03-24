#include "cub3d.h"
#define FOV 0.5

void            my_mlx_pixel_put(t_data data, int x, int y, int color)
{
    char    *dst;

    dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

void            drow_line(t_data data, int current_x, int startY, int endY, int color)
{
    char    *dst;
    while (startY < endY)
    {
        dst = data.addr + (startY * data.line_length + current_x * (data.bits_per_pixel / 8));
        *(unsigned int*)dst = color;
        startY++;
    }
}