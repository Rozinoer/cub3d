/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:16:46 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:16:48 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void print_back(t_game *game)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (x != game->mlx.win_width)
    {
        while (y != game->mlx.win_hight)
        {
            if (y <= game->mlx.win_hight * 0.5)
                my_mlx_pixel_put(game->data, x, y, game->map.ceiling_color);
            else
                my_mlx_pixel_put(game->data, x, y, game->map.floor_color);
            y++;    
        }
        x++;
        y = 0;
    }
}

t_sprt_pos		*sprt_pos_new(int x, int y, int index)
{
	t_sprt_pos *new;

	if (!(new = (t_sprt_pos *)malloc(sizeof(t_sprt_pos))))
		return (NULL);
	if (x < 0)
		new->x = -1;
    else
        new->x = x;
    if (y < 0)
		new->y = -1;
    else
        new->y = y;
    new->index = index;
	new->next = NULL;
	return (new);
}

void	sprt_pos_add_back(t_sprt_pos **lst, t_sprt_pos *new)
{
	t_sprt_pos	*tmp;

	if (lst != NULL)
	{
		tmp = *lst;
		if (*lst == NULL)
			*lst = new;
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = new;
		}
	}
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
	int				i;
	int				j;
	double			tmp;
	int 			x;
	int 			y;
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
				x = get_sprite(game, i)->x;
				y = get_sprite(game, i)->y;
				get_sprite(game, i)->x = get_sprite(game, i + 1)->x;
				get_sprite(game, i)->y = get_sprite(game, i + 1)->y;
				get_sprite(game, i + 1)->x = x;
				get_sprite(game, i + 1)->y = y;
			}
			i++;
		}
		j++;
	}
}