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
