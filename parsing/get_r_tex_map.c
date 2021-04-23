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

static void	write_resolution(t_game *game, char *temp, char *tmp)
{
	temp = skip(temp, 2);
	if (ft_atoi(++temp) > 0)
		game->mlx.win_width = ft_atoi(temp);
	else
		ft_error("Resolution is uncorrect!\n");
	tmp = ft_itoa(game->mlx.win_width);
	temp += ft_strlen(tmp) + 1;
	free(tmp);
	temp = skip(temp, 2);
	if (ft_atoi(temp) > 0)
		game->mlx.win_hight = ft_atoi(temp);
	else
		ft_error("Resolution is uncorrect!\n");
}

int	get_resolution(t_game *game, t_list *list)
{
	char	*tmp;
	char	*temp;

	tmp = NULL;
	while (list->next)
	{
		temp = list->content;
		if (check_identifer(temp, "R ") == 1)
		{
			write_resolution(game, list->content, tmp);
			break ;
		}
		else
			list = list->next;
	}
	return (0);
}

static	char	*check_path(char *path)
{
	char	*str;
	char	*clean;

	str = path;
	while (*path != ' ' && *path)
		path++;
	while (*path != '\0')
	{
		if (*path != ' ' && *path != '\t' && *path != '\0')
			ft_error("Invalid texture path!\n");
		path++;
	}
	str = reverse(str);
	clean = str;
	while (*str == ' ' || *str == '\t')
		str++;
	str = reverse(str);
	free(clean);
	return (str);
}

int	get_texpack(t_game *game)
{
	t_list	*list;
	char	*tmp;

	list = game->param;
	tmp = list->content;
	while (list->next)
	{
		tmp = skip(tmp, 2);
		if (check_identifer(tmp, "NO ") == 1)
			game->map.no_tex = check_path(skip(tmp + 3, 2));
		else if (check_identifer(tmp, "SO ") == 1)
			game->map.so_tex = check_path(skip(tmp + 3, 2));
		else if (check_identifer(tmp, "WE ") == 1)
			game->map.we_tex = check_path(skip(tmp + 3, 2));
		else if (check_identifer(tmp, "EA ") == 1)
			game->map.ea_tex = check_path(skip(tmp + 3, 2));
		else if (check_identifer(tmp, "S ") == 1)
			game->map.sprite_tex = check_path(skip(tmp + 2, 2));
		list = list->next;
		tmp = list->content;
	}
	return (0);
}
