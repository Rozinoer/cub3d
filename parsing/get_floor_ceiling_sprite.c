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

static void	check_val(char **dst)
{
	int		num;
	int		i;
	char	*tmp;

	i = 0;
	while (i < 3)
	{
		tmp = dst[i];
		tmp = skip(tmp, 2);
		if (*tmp == '\0')
			ft_error("Color is invalid!\n");
		num = ft_atoi(dst[i]);
		tmp = tmp + ft_nbrlen(num);
		tmp = skip(tmp, 2);
		if (*tmp != '\0')
			ft_error("Color is invalid!\n");
		i++;
	}
}

static int	check_dst(char **dst)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (dst[i] != NULL)
	{
		i++;
		j++;
	}
	if (j == 3)
	{
		check_val(dst);
		return (0);
	}
	else
		ft_error("Invalid color!\n");
	return (-1);
}

static void	check_str(char *str)
{
	while (*str)
	{
		if (*str != ' ' && (*str < '0' || *str > '9') && *str != ',' \
		&& *str != '\t')
			ft_error("Color is invalid\n");
		str++;
	}
}

int	get_floor_color(t_game *game)
{
	int		i;
	t_list	*list;
	char	**dst;

	i = -1;
	list = game->param;
	dst = NULL;
	while (list->next)
	{
		if (check_identifer(list->content, "F ") != -1)
		{
			list->content = skip(list->content, 2);
			check_str(list->content + 1);
			dst = ft_split(list->content + 2, ',');
			check_dst(dst);
			i = check_color(dst, game, 'F');
			break ;
		}
		list = list->next;
	}
	free(dst[2]);
	free(dst[1]);
	free(dst[0]);
	free(dst);
	return (i);
}

int	get_ceiling_color(t_game *game)
{
	int		i;
	t_list	*list;
	char	**dst;

	i = -1;
	list = game->param;
	dst = NULL;
	while (list->next)
	{
		if (check_identifer(list->content, "C ") != -1)
		{
			list->content = skip(list->content, 2);
			check_str(list->content + 1);
			dst = ft_split(list->content + 2, ',');
			check_dst(dst);
			i = check_color(dst, game, 'C');
			break ;
		}
		list = list->next;
	}
	free(dst[2]);
	free(dst[1]);
	free(dst[0]);
	free(dst);
	return (i);
}
