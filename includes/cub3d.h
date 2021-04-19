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
# define texHeight 64
# define texWidth 64
# define sprtHeight 16
# define sprtWidth 16

typedef struct  s_data {
	void        *img;
	char        *addr;
	int         bits_per_pixel;
	int         line_length;
	int         endian;
	int         height;
	int         width;
	double			step;
	double			pos;
	int				x;
	int				y;
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
	float       posX;
	float       posY;
	float       oldX;
	float       oldY;
	double      sideDistX;
	double      sideDistY;
	double      rotation_angle ;
	double		dirX;
	double      dirY;
	double		planeX;
	double		planeY;
	double      to_wall;
	double      to_sprite;
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

typedef struct s_texture
{
	t_data *wall_n;
	t_data *wall_s;
	t_data *wall_w;
	t_data *wall_e;
	t_data *sprite;
	t_data *current;
	int color;
	int				texX;
	int				texY;
	double			wallX;
	double step;
	double texPos;
}               t_texture;

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

typedef struct		s_sprt {
	double			x;
	double			y;
	double			inv_det;
	double			transform_x;
	double			transform_y;
	int				sprite_screen_x;
	int				sprite_height;
	int				draw_start_y;
	int				draw_end_y;
	int				sprite_width;
	int				draw_start_x;
	int				draw_end_x;
	int				txtr_x;
	int				txtr_y;
	int				color;
	int				d;
	int				amount_sprt;
}					t_sprt;

typedef struct s_sprt_pos
{
	int		x;
	int		y;
	int		index;
	struct s_sprt_pos *next;
}				t_sprt_pos;

typedef struct s_game
{
	t_mlx       mlx;
	t_texture   txtr;
	t_map       map;
	t_list      *param;
	t_list      *pointer;
	t_player    player;
	t_data      data;
	t_ray       ray;
	t_sprt		sprites;
	t_sprt_pos	*sprt_pos;
	int         save;
	int				*arr_sp;
	double			*z_buff;
	int				*spr_oder;
	double			*spr_dist;
}               t_game;

void    parser(t_game *game, char *str);
void    print_map(t_game *game);
void    print_player(t_game *game);
int     key_released(int keycode, t_game *game);
int     key_pressed(int keycode, t_game *game);
int     update(t_game *game);
void    my_mlx_pixel_put(t_data data, int x, int y, int color);
int     render_next_frame(t_game *game);
void    print_ray(t_game *game);
void    print_back(t_game *game);
int     check_identifer(char *str, char *iden);
int     check_map(t_game *game);
int     check_color(char *str, t_game *game, char c);
int     get_floor_color(t_game *game);
int     get_ceiling_color(t_game *game);
void    my_mlx_pixel_put(t_data data, int x, int y, int color);
void    init_struct(t_game *game);
int     check_map(t_game *game);
void    drow_line(t_data data, int x, int startY, int endY, int color);
int     screenshot(t_game *game);
void    ft_error(char *str);
int     get_texpack(t_game *game);
int     get_resolution(t_game *game);
int     get_map(t_game *game);
int		ft_get_pxl_clr(t_data *txtr, int x, int y);
int 	init_sprite(t_game *game);
int 	render_sprite(t_game *game, int x);
void				ft_calc_spr(t_sprt_pos *sprite, t_player player, t_game *game);
int init_sprite_structure(t_game *game);
t_sprt_pos		*sprt_pos_new(int x, int y, int index);
void	sprt_pos_add_back(t_sprt_pos **lst, t_sprt_pos *new);
void				ft_draw_spr(t_game *game, int txt_w, int txt_h);
#endif