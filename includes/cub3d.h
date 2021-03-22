#ifndef CUB3D_H
# define CUB3D_H

#include "../res/libft/libft.h"
#include "get_next_line.h"
#include "../minilibx_opengl_20191021/mlx.h"
#include <fcntl.h>
#include <math.h>
#define TILE_SIZE 32
#include <stdio.h>
# define FILE_BMP "cub3D.bmp"
# define ALLBMPHEADER 54
# define W 13
# define S 1
# define D 2
# define A 0


typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

typedef struct s_ray
{
    int stepX;
    int stepY;
    int mapX;
    int mapY;
    double  deltaDistX;
    double  deltaDistY;
    int     lineHeight;
    int      drawStart;
    int      drawEnd;
}               t_ray;

typedef struct s_player
{
    float       posX ;
	float       posY;
    double      sideDistX;
    double      sideDistY;
	double      rotation_angle ;
    double		dirX;
	double      dirY;
	double		planeX;
	double		planeY;
    double      to_wall;
    char        direct;
    int         hit;
    int         side;
}               t_player;

typedef struct s_map
{
    char    **map;
    int     map_size;
    int     color;
    int     floor_color;
    int     ceiling_color;
    char *no_tex;
    char *so_tex;
    char *we_tex;
    char *ea_tex;
    char *sprite_tex;
}               t_map;

typedef struct s_mlx
{
    void    *mlx;
    void    *mlx_win;
    int     win_hight;
    int     win_width;
    int     monitor_hight;
    int     monitor_width;
    char    *file;
}               t_mlx;

typedef struct s_game
{
    t_mlx       mlx;
    t_map       map;
    t_list      *param;
    t_list      *pointer;
    t_player    player;
    t_data      data;
    t_ray      ray;
    int         save;
}               t_game;

int     init(t_game *game);
void    parser(t_game *game, char *str);
void    get_param(t_game *game);
void    print_map(t_game *game);
void    print_player(t_game *game);
int     key_released(int keycode, t_game *game);
int     key_pressed(int keycode, t_game *game);
int     update(t_game *game);
void    my_mlx_pixel_put(t_data data, int x, int y, int color);
int     render_next_frame(t_game *game);
void    print_ray(t_game *game);
void    print_back(t_game *game);
int     error(int error, char c, t_game *game);
int     check_identifer(char *str, char *iden);
int     check_map(t_game *game);
int     get_sprite_tex(t_game *game);
int     check_color(char *str, t_game *game, char c);
int     get_floor_color(t_game *game);
int     get_ceiling_color(t_game *game);
void    my_mlx_pixel_put(t_data data, int x, int y, int color);
void    get_pos(t_player *player, t_game *game);
void    init_struct(t_game *game);
int     check_map(t_game *game);
void    drow_line(t_data data, int x, int startY, int endY, int color);
int     screenshot(t_game *game);
#endif