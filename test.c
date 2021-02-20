#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "minilibx_opengl_20191021/mlx.h"

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

char*            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;

	return(dst);
}

int main()
{
	void    *mlx;
    void    *mlx_win;
    t_data  img;
	char *dst;
	clock_t start, stop;

	start = clock();
    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
    img.img = mlx_new_image(mlx, 500 / 10, 500 / 10);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    my_mlx_pixel_put(&img, 50, 10, 0x00FF00);

    mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	printf("dst = %s\n",dst);
	stop = clock();
	printf("time_start = %lu\n time_end = %lu\n, average = %lu\n",start, stop, (stop - start));
    mlx_loop(mlx);
}