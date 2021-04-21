/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:17:27 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:17:29 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#define FOV 0.5

void            my_mlx_pixel_put(t_data data, int x, int y, int color)
{
    char    *dst;

    dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int			ft_get_pxl_clr(t_data *txtr, int x, int y)
{
	int		*ptr;
	int		color;

	ptr = (void *)txtr->addr + (y * txtr->line_length + x * \
												(txtr->bits_per_pixel / 8));
	color = *(int*)ptr;
	return (color);
}

int    close_programm(__unused t_game *game)
{
    mlx_destroy_image(game->mlx.mlx, game->data.img);
	mlx_clear_window(game->mlx.mlx, game->mlx.mlx_win);
	mlx_destroy_window(game->mlx.mlx, game->mlx.mlx_win);

    exit(0);
}