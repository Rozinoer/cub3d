/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dmyesha <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/22 19:21:45 by dmyesha           #+#    #+#             */
/*   Updated: 2021/04/22 19:21:48 by dmyesha          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	empty_line(char *str)
{
	if (*str == '\0')
		return (1);
	else
		return (0);
}

static t_list	*check_empty_line(t_list *tmp)
{
	char	*str;

	str = tmp->content;
	while (tmp->next)
	{
		while (*str)
		{
			if (*str == ' ' || *str == '\t')
				str++;
			else
				return (tmp);
		}
		tmp = tmp->next;
		str = tmp->content;
	}
	while (*str)
	{
		if (*str == ' ' || *str == '\t')
			str++;
		else
			return (tmp);
	}
	return (NULL);
}

static void	allocate_map(t_game *game, t_list *tmp)
{
	int		size;
	int		i;

	i = -1;
	tmp = check_empty_line(tmp);
	size = ft_lstsize(tmp);
	game->map.map = ft_calloc(size + 1, sizeof(char *));
	game->map.map[size] = NULL;
	if (!(game->map.map))
		ft_error("Memory is not allocate for map!\n");
	game->map.map_size = size;
	while (tmp)
	{
		game->map.map[++i] = tmp->content;
		if (empty_line(tmp->content))
			game->flag = 1;
		if (!empty_line(tmp->content) && game->flag == 1)
			ft_error("Empty lines after map!\n");
		tmp = tmp->next;
	}
	check_map(game);
}

void	get_map(t_game *game, int i)
{
	t_list	*tmp;

	i = 0;
	tmp = game->param;
	while (i != 8)
	{
		if (check_identifer(tmp->content, "R ") > 0)
			i++;
		else if (check_identifer(tmp->content, "NO ") > 0)
			i++;
		else if (check_identifer(tmp->content, "SO ") > 0)
			i++;
		else if (check_identifer(tmp->content, "WE ") > 0)
			i++;
		else if (check_identifer(tmp->content, "EA ") > 0)
			i++;
		else if (check_identifer(tmp->content, "S ") > 0)
			i++;
		else if (check_identifer(tmp->content, "F ") > 0)
			i++;
		else if (check_identifer(tmp->content, "C ") > 0)
			i++;
		tmp = tmp->next;
	}
	allocate_map(game, tmp);
}
