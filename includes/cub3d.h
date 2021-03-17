#ifndef CUB3D_H
# define CUB3D_H

#include "../res/libft/libft.h"
#include "get_next_line.h"
#include "../minilibx_opengl_20191021/mlx.h"
#include <fcntl.h>
#include <math.h>
# define TILE_SIZE 16
# define screenWidth 1920
# define screenHight 1080
#include <stdio.h>

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


typedef struct s_player
{
    float posX ;
	float posY ;
	int radius ;
	int turn_dir ; // -1 left, +1 right
	int walk_dir ;
	double rotation_angle ;
	double rotation_speed ;
	double move_speed ;
    double right_move;
    double left_move;
    int to_wall;
    char direct;
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
}               t_mlx;

typedef struct s_game
{
    t_mlx   mlx;
    t_map   map;
    t_list  *param;
    t_list  *pointer;
    t_player player;
    t_data   data;
    // t_ray   ray;
}               t_game;

int     init(t_game *game);
void    parser(t_game *game);
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
#endif