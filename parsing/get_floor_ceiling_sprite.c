/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_floor_ceiling_sprite.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:13:39 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:13:42 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_floor_color(t_game *game)
{
	int		i;
	t_list	*list;

	i = -1;
	list = game->param;
	while (list->next)
	{
		if (check_identifer(list->content, "F ") != -1)
		{
			i = check_color(list->content + 2, game, 'F');
			break ;
		}
		list = list->next;
	}
	return (i);
}

int	get_ceiling_color(t_game *game)
{
	int		i;
	t_list	*list;

	i = -1;
	list = game->param;
	while (list->next)
	{
		if (check_identifer(list->content, "C ") != -1)
		{
			i = check_color(list->content + 2, game, 'C');
			break ;
		}
		list = list->next;
	}
	return (i);
}
