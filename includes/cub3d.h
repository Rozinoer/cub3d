/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 17:44:13 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 18:35:43 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../res/libft/libft.h"
# include "get_next_line.h"
# include "../minilibx_opengl_20191021/mlx.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# define TILE_SIZE 32
# define FILE_BMP "cub3D.bmp"
# define ALLBMPHEADER 54
# define W 13
# define S 1
# define D 2
# define A 0
# define TEXHEIGHT 64
# define TEXWIDTH 64
# define FOV 0.5

typedef struct s_data
{
	void				*img;
	char				*addr;
	int					bits_per_pixel;
	int					line_length;
	int					endian;
	int					height;
	int					width;
	double				step;
	double				pos;
	int					x;
	int					y;
}						t_data;

typedef struct s_ray
{
	int					step_x;
	int					step_y;
	int					map_x;
	int					map_y;
	double				delta_distx;
	double				delta_disty;
	int					line_height;
	int					draw_start;
	int					draw_end;
}						t_ray;

typedef struct s_player
{
	float				pos_x;
	float				pos_y;
	float				old_x;
	float				old_y;
	double				side_distx;
	double				side_disty;
	double				rotation_angle;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
	double				to_wall;
	double				to_sprite;
	char				direct;
	int					hit;
	int					side;
}						t_player;

typedef struct s_map
{
	char				**map;
	int					map_size;
	int					color;
	int					floor_color;
	int					ceiling_color;
	char				*no_tex;
	char				*so_tex;
	char				*we_tex;
	char				*ea_tex;
	char				*sprite_tex;
}						t_map;

typedef struct s_texture
{
	t_data				*wall_n;
	t_data				*wall_s;
	t_data				*wall_w;
	t_data				*wall_e;
	t_data				*sprite;
	t_data				*current;
	int					color;
	int					tex_x;
	int					tex_y;
	double				wall_x;
	double				step;
	double				tex_pos;
}						t_texture;

typedef struct s_mlx
{
	void				*mlx;
	void				*mlx_win;
	int					win_hight;
	int					win_width;
	int					monitor_hight;
	int					monitor_width;
	char				*file;
}						t_mlx;

typedef struct s_sprt
{
	double				x;
	double				y;
	double				inv_det;
	double				transform_x;
	double				transform_y;
	int					sprite_screen_x;
	int					sprite_height;
	int					draw_start_y;
	int					draw_end_y;
	int					sprite_width;
	int					draw_start_x;
	int					draw_end_x;
	int					txtr_x;
	int					txtr_y;
	int					color;
	int					d;
	int					amount_sprt;
}						t_sprt;

typedef struct s_sprt_pos
{
	int					x;
	int					y;
	int					index;
	struct s_sprt_pos	*next;
}						t_sprt_pos;

typedef struct s_game
{
	t_mlx				mlx;
	t_texture			txtr;
	t_map				map;
	t_list				*param;
	t_list				*pointer;
	t_player			player;
	t_data				data;
	t_ray				ray;
	t_sprt				sprites;
	t_sprt_pos			*sprt_pos;
	t_sprt_pos			*tmp;
	t_sprt_pos			*temp;
	int					save;
	int					*arr_sp;
	double				*z_buff;
	int					*spr_oder;
	double				*spr_dist;
	int					current_x;
}						t_game;

void					parser(t_game *game, char *str);
void					print_map(t_game *game);
void					print_player(t_game *game);
int						key_released(int keycode, t_game *game);
int						key_pressed(int keycode, t_game *game);
int						update(t_game *game);
void					my_mlx_pixel_put(t_data data, int x, int y, int color);
int						render_next_frame(t_game *game);
void					print_ray(t_game *game);
void					print_back(t_game *game);
int						check_identifer(char *str, char *iden);
int						check_map(t_game *game);
int						check_color(char *str, t_game *game, char c);
int						get_floor_color(t_game *game);
int						get_ceiling_color(t_game *game);
void					my_mlx_pixel_put(t_data data, int x, int y, int color);
void					init_struct(t_game *game);
int						check_map(t_game *game);
int						screenshot(t_game *game);
void					ft_error(char *str);
int						get_texpack(t_game *game);
int						get_resolution(t_game *game);
int						get_map(t_game *game);
int						ft_get_pxl_clr(t_data *txtr, int x, int y);
int						init_sprite(t_game *game);
int						render_sprite(t_game *game, int x);
void					spr(t_sprt_pos *sprite, t_player player, t_game *game);
int						init_sprite_structure(t_game *game);
t_sprt_pos				*sprt_pos_new(int x, int y, int index);
t_sprt_pos				*get_sprite(t_game *game, int index);
void					sprt_pos_add_back(t_sprt_pos **lst, t_sprt_pos *new);
void					ft_draw_spr(t_game *game, int txt_w, int txt_h);
void					allocate_memory(t_game *game);
#endif
