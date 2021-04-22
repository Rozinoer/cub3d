/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 18:52:42 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 18:52:45 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_pos(t_player *player, t_game *game)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < game->map.map_size)
	{
		while (game->map.map[i][j] != '\0')
		{
			if (game->map.map[i][j] == 'N' || game->map.map[i][j] == 'S' ||
			game->map.map[i][j] == 'W' || game->map.map[i][j] == 'E')
			{
				player->direct = game->map.map[i][j];
				player->pos_x = j;
				player->pos_y = i;
				break ;
			}
			j++;
		}
		i++;
		j = 0;
	}
}

static void	ft_set_pos_player(t_game *game)
{
	if (game->player.direct == -1)
		ft_error("Player position not found\n");
	if (game->player.direct == 'N')
	{
		game->player.dir_y = -1;
		game->player.plane_x = FOV;
	}
	else if (game->player.direct == 'S')
	{
		game->player.dir_y = 1;
		game->player.plane_x = -FOV;
	}
	else if (game->player.direct == 'W')
	{
		game->player.dir_x = -1;
		game->player.plane_y = -FOV;
	}
	else if (game->player.direct == 'E')
	{
		game->player.dir_x = 1;
		game->player.plane_y = FOV;
	}
}

static t_data	*ft_create_img_txtr(char *file, void *ptr_mlx)
{
	t_data	*txtr;

	txtr = malloc(sizeof(t_data));
	if (!(txtr))
		ft_error("Error memory allocation\n");
	txtr->img = mlx_xpm_file_to_image(ptr_mlx, file, \
							&txtr->width, &txtr->height);
	if (!txtr->img)
		ft_error("Error map: error texture\n");
	txtr->addr = mlx_get_data_addr(txtr->img, &txtr->bits_per_pixel, \
							&txtr->line_length, &txtr->endian);
	return (txtr);
}

static int	init(t_game *game)
{
	game->mlx.mlx = mlx_init();
	game->mlx.mlx_win = mlx_new_window(game->mlx.mlx, game->mlx.win_width, \
	game->mlx.win_hight, "cub3d");
	game->txtr.wall_n = ft_create_img_txtr(game->map.no_tex, game->mlx.mlx);
	game->txtr.wall_s = ft_create_img_txtr(game->map.so_tex, game->mlx.mlx);
	game->txtr.wall_e = ft_create_img_txtr(game->map.ea_tex, game->mlx.mlx);
	game->txtr.wall_w = ft_create_img_txtr(game->map.we_tex, game->mlx.mlx);
	game->txtr.sprite = ft_create_img_txtr(game->map.sprite_tex, game->mlx.mlx);
	return (0);
}

void	init_struct(t_game *game)
{
	t_player	player;

	player.dir_x = 0;
	player.dir_y = 0;
	player.plane_x = 0;
	player.plane_y = 0;
	player.direct = -1;
	mlx_get_screen_size(&game->mlx.monitor_width, &game->mlx.monitor_hight);
	parser(game, game->mlx.file);
	get_pos(&player, game);
	if (player.direct != -1)
	{
		player.pos_x += 0.5;
		player.pos_y += 0.5;
	}
	game->player = player;
	ft_set_pos_player(game);
	init(game);
	game->data.img = mlx_new_image(game->mlx.mlx, game->mlx.win_width, \
	game->mlx.win_hight);
	game->data.addr = mlx_get_data_addr(game->data.img, \
	&game->data.bits_per_pixel, &game->data.line_length, \
								 &game->data.endian);
}
