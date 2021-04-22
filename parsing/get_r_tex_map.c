/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_r_tex_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/20 20:15:31 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/20 20:15:41 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_resolution(t_game *game, t_list *list)
{
	char	*tmp;
	char	*temp;

	while (list->next)
	{
		temp = list->content;
		if (check_identifer(temp, "R ") == 1)
		{
			temp = skip(temp, 2);
			if (ft_atoi(++temp) > 1)
				game->mlx.win_width = ft_atoi(temp);
			else
				ft_error("Error. Resolution is uncorrect!\n");
			tmp = ft_itoa(game->mlx.win_width);
			temp += ft_strlen(tmp) + 1;
			free(tmp);
			temp = skip(temp, 2);
			if (ft_atoi(temp) > 1)
				game->mlx.win_hight = ft_atoi(temp);
			else
				ft_error("Error. Resolution is uncorrect!\n");
			break ;
		}
		else
			list = list->next;
	}
	return (0);
}

int	get_texpack(t_game *game)
{
	t_list	*list;

	list = game->param;
	while (list->next)
	{
		list->content = skip(list->content, 2);
		if (check_identifer(list->content, "NO ") == 1)
			game->map.no_tex = skip(list->content + 3, 2);
		if (check_identifer(list->content, "SO ") == 1)
			game->map.so_tex = skip(list->content + 3, 2);
		if (check_identifer(list->content, "WE ") == 1)
			game->map.we_tex = skip(list->content + 3, 2);
		if (check_identifer(list->content, "EA ") == 1)
			game->map.ea_tex = skip(list->content + 3, 2);
		if (check_identifer(list->content, "S ") == 1)
			game->map.sprite_tex = skip(list->content + 2, 2);
		list = list->next;
	}
	return (0);
}
