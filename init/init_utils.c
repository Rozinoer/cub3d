/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 18:26:05 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/23 18:26:06 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	double_pos(t_player *player, int x, int y, char c)
{
	if (player->direct == -1)
	{
		player->direct = c;
		player->pos_x = x;
		player->pos_y = y;
	}
	else
		ft_error("Too many player spawn!\n");
}
