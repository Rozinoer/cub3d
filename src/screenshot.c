/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:17:12 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:17:15 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
# define PMOD 0644
# define BITMAPINFO_SIZE 40

static void			ft_bmp_header_init(unsigned char *buf, t_game *game)
{
	unsigned int	size;

	size = game->mlx.win_width * game->mlx.win_hight + ALLBMPHEADER;
	buf[0] = (unsigned char)'B';
	buf[1] = (unsigned char)'M';
	buf[2] = size;
	buf[3] = size >> 8;
	buf[4] = size >> 16;
	buf[5] = size >> 24;
	buf[10] = ALLBMPHEADER;
	buf[14] = BITMAPINFO_SIZE;
	buf[18] = game->mlx.win_width;
	buf[19] = game->mlx.win_width >> 8;
	buf[20] = game->mlx.win_width >> 16;
	buf[21] = game->mlx.win_width >> 24;
	buf[22] = game->mlx.win_hight;
	buf[23] = game->mlx.win_hight >> 8;
	buf[24] = game->mlx.win_hight >> 16;
	buf[25] = game->mlx.win_hight >> 24;
	buf[26] = 1;
	buf[28] = game->data.bits_per_pixel;
}

static void			ft_create_bmp(t_game *game)
{
	int				fd;
	int				i;
	int				j;
	unsigned char	buf[ALLBMPHEADER];

	ft_bzero(buf, 54);
	ft_bmp_header_init(buf, game);
	if ((fd = open(FILE_BMP, O_CREAT | O_RDWR | O_TRUNC, PMOD)) == -1)
		ft_putstr("Error create bmp file: fd = -1\n");
	write(fd, buf, ALLBMPHEADER);
	i = game->mlx.win_hight - 1;
	j = (game->data.bits_per_pixel / 8) * game->mlx.win_width;
	while (i >= 0)
	{
		write(fd, &game->data.addr[i * game->data.line_length], j);
		i--;
	}
	close(fd);
}

int     screenshot(t_game *game)
{
	ft_create_bmp(game);
	mlx_destroy_image(game->mlx.mlx, game->data.img);
    mlx_destroy_window(game->mlx.mlx, game->mlx.mlx_win);
	exit(0);
}
