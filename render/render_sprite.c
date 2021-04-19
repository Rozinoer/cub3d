#include "cub3d.h"

void				ft_draw_spr(t_game *game, int txt_w, int txt_h)
{
	int				x;
	int				y;

	x = game->sprites.draw_start_x;
	while (x < game->sprites.draw_end_x)
	{
		game->sprites.txtr_x = (int)(256 * (x - (-game->sprites.sprite_width / 2 + \
					game->sprites.sprite_screen_x)) * txt_w / game->sprites.sprite_width) / 256;
		if (game->sprites.transform_y > 0 && x > 0 && x < game->mlx.win_width && \
				game->sprites.transform_y < game->z_buff[x])
		{
			y = game->sprites.draw_start_y;
			while (y < game->sprites.draw_end_y)
			{
				game->sprites.d = (y) * 256 - game->mlx.win_hight * 128 + game->sprites.sprite_height * 128;
				game->sprites.txtr_y = ((game->sprites.d * txt_h) / game->sprites.sprite_height) / 256;
				game->sprites.color = ft_get_pxl_clr(game->txtr.sprite, game->sprites.txtr_x, \
																game->sprites.txtr_y);
				if ((game->sprites.color & 0x00FFFFFF) != 0)
					my_mlx_pixel_put(game->data, x, y, game->sprites.color);
				y++;
			}
		}
		x++;
	}
}

void				ft_calc_spr(t_sprt_pos *sprite, t_player player, t_game *game)
{	
	game->sprites.x = (double)sprite->x + 0.5 - player.posX;
	game->sprites.y = (double)sprite->y + 0.5 - player.posY;
	game->sprites.inv_det = 1.0 / (player.planeX * player.dirY - player.dirX * player.planeY);
	game->sprites.transform_x = game->sprites.inv_det * (player.dirY * game->sprites.x - \
										player.dirX * game->sprites.y);
	game->sprites.transform_y = game->sprites.inv_det * (-player.planeY * game->sprites.x + \
														player.planeX * game->sprites.y);
	game->sprites.sprite_screen_x = (int)((game->mlx.win_width / 2) * \
							(1 + game->sprites.transform_x / game->sprites.transform_y));
	game->sprites.sprite_height = abs((int)(game->mlx.win_hight / (game->sprites.transform_y)));
	game->sprites.draw_start_y = -game->sprites.sprite_height / 2 + game->mlx.win_hight / 2;
	if (game->sprites.draw_start_y < 0)
		game->sprites.draw_start_y = 0;
	game->sprites.draw_end_y = game->sprites.sprite_height / 2 + game->mlx.win_hight / 2;
	if (game->sprites.draw_end_y >= game->mlx.win_hight)
		game->sprites.draw_end_y = game->mlx.win_hight - 1;
	game->sprites.sprite_width = abs((int)(game->mlx.win_hight / (game->sprites.transform_y)));
	game->sprites.draw_start_x = -game->sprites.sprite_width / 2 + game->sprites.sprite_screen_x;
	if (game->sprites.draw_start_x < 0)
		game->sprites.draw_start_x = 0;
	game->sprites.draw_end_x = game->sprites.sprite_width / 2 + game->sprites.sprite_screen_x;
	if (game->sprites.draw_end_x >= game->mlx.win_width)
		game->sprites.draw_end_x = game->mlx.win_width - 1;
}

int init_sprite_structure(t_game *game)
{
    int	x;
	int	y;
	int				ind;

	x = 0;
	y = 0;
	ind = 0;
	if(!(game->sprt_pos = malloc(sizeof(t_sprt_pos))))
		ft_error("Error memory allocation\n");
	if (!(game->spr_dist = malloc(game->sprites.amount_sprt * sizeof(double))))
		ft_error("Error memory allocation\n");
	if (!(game->spr_oder = malloc(game->sprites.amount_sprt * sizeof(int))))
		ft_error("Error memory allocation\n");
	while (y < game->map.map_size)
	{
		while (game->map.map[y][x] != '\0')
		{
			if (game->map.map[y][x] == '2')
			{
				sprt_pos_add_back(&game->sprt_pos, sprt_pos_new(x, y, ind));
				ind++;
			}
			x++;
		}
		y++;
		x = 0;
	}
	if (!(game->z_buff = malloc(game->mlx.win_width * sizeof(double))))
		ft_error("Error memory allocation\n");
	
	t_sprt_pos *tmp = game->sprt_pos;
	game->sprt_pos = tmp->next;
	free(tmp);
    return (0);
}

t_sprt_pos *get_sprite(t_game *game, int index)
{
	t_sprt_pos *tmp;

	tmp = game->sprt_pos;
	while(tmp->next != NULL)
	{
		if (tmp->index == index)
			return (tmp);
		tmp = tmp->next;
	}
	if (tmp->index == index)
		return (tmp);
	return (NULL);
}

void				ft_sort(t_game *game)
{
	int	i;
	int	j;
	double			tmp;
	int				temp_i;

	j = 0;
	while (j < game->sprites.amount_sprt - 1)
	{
		i = 0;
		while (i < game->sprites.amount_sprt - j - 1)
		{
			if (game->spr_dist[i] < game->spr_dist[i + 1])
			{
				tmp = game->spr_dist[i];
				game->spr_dist[i] = game->spr_dist[i + 1];
				game->spr_dist[i + 1] = tmp;
				temp_i = game->spr_oder[i];
				game->spr_oder[i] = game->spr_oder[i + 1];
				game->spr_oder[i + 1] = temp_i;
			}
			i++;
		}
		j++;
	}
}

int init_sprite(t_game *game)
{
	int	i;
	double			spr_x;
	double			spr_y;

	i = 0;
	while (i < game->sprites.amount_sprt)
	{
		game->spr_oder[i] = i;
		spr_x = (double)get_sprite(game, i)->x + 0.5;
		spr_y = (double)get_sprite(game, i)->y + 0.5;
		game->spr_dist[i] = (pow((game->player.posX - spr_x), 2) + \
								pow((game->player.posY - spr_y), 2));
		i++;
	}
	ft_sort(game);
	return (0);
}